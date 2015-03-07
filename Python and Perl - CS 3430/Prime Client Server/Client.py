# Jonathan Petersen
# A01236750
# Prime Client Server Assignment
# Client Code

import socket;

# Setup the connection
clientSocket = socket.socket();
# serverName = socket.gethostname(); 		# Change this for a nonlocal server.
serverPort = 21758;

# Connect and recieve data.
clientSocket.connect(('', serverPort));
clientSocket.send("1000")					# Change this value to send a different Number
print clientSocket.recv(1024);
