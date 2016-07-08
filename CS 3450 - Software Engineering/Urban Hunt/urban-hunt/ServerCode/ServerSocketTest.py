import socket

class SynchronousServer:
	def __init__(self, portnum):
		self.ServerSocket = socket.socket()
		self.host = socket.gethostname()
		print 'host:', self.host
		self.port = portnum
		print 'port:', self.port
		self.ServerSocket.bind((self.host, self.port))
		self.ServerSocket.listen(5)
	def acceptRequest(self):
		print "Receiving Requests: \n"
		clientSocket, clientAddress = self.ServerSocket.accept()
		testRecv = clientSocket.recv(1024)
		print testRecv;
		clientSocket.close()

def main():
	port = 21000
	server = SynchronousServer(port)
	server.acceptRequest()

main()