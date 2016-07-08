
# Socket Test
# Anthony Kiesel     / Initial Implementation
# Kenny Fryar-Ludwig / Added incoming message parsing

import socket
import json
import datetime
import sys
from enum import Enum

class Game:
  def __init__(self, gameId = "UNASSIGNED", type = "NONE", host = -1):
    self.isActive = False
    self.id = gameId
    self.numberOfTeams = 0
    self.hostId = host
    self.gameType = type
    self.startTime = datetime.datetime.now()
    self.players = []

  def Print(self):
    print "-- -- -- -- -- -- -- -- -- -- -- --"
    print self.gameType + "-based game has the id " + str(self.id)
    print "It has " + str(self.numberOfTeams) + " teams and " + str(len(self.players)) + " players."
    print "It started at " + str(self.startTime)
    if self.isActive:
      print "It's currently active"
    else:
      print "It's currently inactive"
    print "-- -- -- -- -- -- -- -- -- -- -- --"

class Player:
  def __init__(self, pid = -1, gid = -1, did = -1, stat = "INACTIVE", lat = -1, long = -1):
    self.playerId = pid
    self.gameId = gid
    self.phoneId = did
    self.status = stat
    self.latitude = lat
    self.longitude = long
    self.socket = None

class SCRIPT_ACTION(Enum):
  # # COMMANDS TO BE USED BY APP ##
  GAME_INIT = 1
  GAME_EDIT = 2
  PLAYER_INIT = 3
  PLAYER_EDIT = 4
  PLAYER_UPDATE_LOC = 5

  # # SERVER USE ONLY. DO NOT CALL FROM APP ##
  RESERVED = 6
  SEND_LOC_TO_PLAYERS = 7
  DEBUG_INFO = 8
  QUIT_SCRIPT = 9
  SERVER_WAIT = 0

class SynchronousServer:
  def __init__(self, portnum):
    self.gameList = []
    self.ServerSocket = socket.socket()
    self.host = socket.gethostname()
    print 'host:', self.host
    self.port = portnum
    print 'port:', self.port
    self.ServerSocket.bind((self.host, self.port))
    self.ServerSocket.listen(5)

  def receiveMessage(self):
    print "\n Receiving Requests: \n"
    clientSocket, unusedData = self.ServerSocket.accept()
    return json.JSONDecoder().decode(clientSocket.recv(1024)), clientSocket

  def sendMessage(self, clientSocket, message):
    print "\n Sending Response\n"
    dataToSend = json.JSONEncoder().encode(message)
    clientSocket.send(dataToSend)
    clientSocket.close()

  def handleMessage(self, incomingMessage, clientSocket):
    outgoingMessage = "NO MESSAGE"

    if not u'command' in incomingMessage:
      return "Invalid packet."

    elif (incomingMessage[u'command'] <= 0 and incomingMessage[u'command'] <= 9):
      return "Invalid packet."

    print(incomingMessage)

    # Parses message - if valid it creates a new game
    if (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.GAME_INIT):
      try:
        tempGame = Game()

	#print(incomingMessage[u'gameId'])
	#print(incomingMessage[u'hostId'])

        tempGame = Game(incomingMessage[u'gameId'])
        tempGame.hostId = incomingMessage[u'hostId']
        tempGame.isActive = True
        tempGame.numberOfTeams = 1
        tempGame.startTime = datetime.datetime.now()
        tempGame.players = []

        self.gameList.append(tempGame)
        print "Game " + str(tempGame.id) + " has been created"
        tempGame.Print()
      except:
	print sys.exc_info()
        print "Game failed to create. Not all parameters were provided as expected."
        outgoingMessage = "Game failed to create. Not all parameters were provided as expected."

    # Parses message - if valid it applies new values to the game in question
    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.GAME_EDIT):
      try:
        print "Edit the game's info!"
        for game in self.gameList:
          if incomingMessage[u'gameId'] == game.id:
            tempGame = Game(incomingMessage[u'gameId'])
            tempGame.hostId = incomingMessage[u'hostId']
            tempGame.isActive = True
            tempGame.numberOfTeams = 1
            tempGame.startTime = datetime.datetime.now()
            tempGame.players = []

      except:
        print "Somehow this failed..."
    # Parses message - if valid it creates a new player for the game
    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.PLAYER_INIT):
      try:
        tempPlayer = Player()
        for game in self.gameList:
          if incomingMessage[u'gameId'] == game.id:
            tempPlayer.playerId = incomingMessage[u'pid']
            tempPlayer.gameId = incomingMessage[u'gid']
            tempPlayer.socket = clientSocket
            tempPlayer.status = incomingMessage[u'stat']
            tempPlayer.latitude = incomingMessage[u'lat']
            tempPlayer.longitude = incomingMessage[u'long']

            game.players.append(tempPlayer)
            outgoingMessage = "Successfully created the player " + tempPlayer.playerId
            break

      except:
        outgoingMessage = "Invalid parameters - unable to create player"

    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.PLAYER_EDIT):
      print "Edit the player!"
      try:
        for game in self.gameList:
          if incomingMessage[u'gameId'] == game.id:
            for player in self.playerList:
              if (player.playerId == incomingMessage[u'pid']):
                player.playerId = incomingMessage[u'pid']
                player.gameId = incomingMessage[u'gid']
                player.socket = clientSocket
                player.status = incomingMessage[u'stat']
                player.latitude = incomingMessage[u'lat']
                player.longitude = incomingMessage[u'long']

                game.players.append(tempPlayer)
                outgoingMessage = "Successfully edited the player " + tempPlayer.playerId
                break

      except:
        outgoingMessage = "Invalid parameters - unable to edit the player"

    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.PLAYER_UPDATE_LOC):
      print "We've recieved a new player location. Let's update it"
      try:
        for game in self.gameList:
          if incomingMessage[u'gameId'] == game.id:
            for player in game.players:
              if (player.playerId == incomingMessage[u'pid']):
                player.latitude = incomingMessage[u'lat']
                player.longitude = incomingMessage[u'long']

                # game.players.append(tempPlayer)
                outgoingMessage = "Successfully edited the player's location"
                break

      except:
	print(sys.exc_info())
        outgoingMessage = "Invalid parameters - unable to edit location"

    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.SEND_LOC_TO_PLAYERS):
      print "Sending location info updates to each player"
      try:
        for game in self.gameList:
          if incomingMessage[u'gameId'] == game.id:
            count = 0
            playerString = "num,pid,status,lat,long;"
            for player in self.playerList:
              playerString += str(count)
              playerString += str(player.playerId) + ","
              playerString += str(player.status) + ","
              playerString += str(player.latitude) + ","
              playerString += str(player.longitude) + ";"

              count += 1
            outgoingMessage = playerString

      except:
        outgoingMessage = "Something went wrong - we can't get player information"

    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.RESERVED):
      print "Move Along, nothing to see here"

    elif (SCRIPT_ACTION(incomingMessage[u'command']) == SCRIPT_ACTION.QUIT_SCRIPT):
      print "Quitting server script"
      exit()

    return outgoingMessage

  def sendAndReceive(self):
    while(True):
      incomingMessage, clientSocket = self.receiveMessage()

      if (incomingMessage == None):
        continue

      outgoingMessage = self.handleMessage(incomingMessage, clientSocket)

      self.sendMessage(clientSocket, outgoingMessage)


def main():
  port = 21000
  server = SynchronousServer(port)
  server.sendAndReceive()

main()



