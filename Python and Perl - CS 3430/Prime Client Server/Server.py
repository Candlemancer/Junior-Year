# Jonathan Petersen
# A01236750
# Prime Client Server Assignment
# Server Code

import socket;
import math;

def getPrimes(upperBound) :

	# Error Handling
	if (upperBound < 0) :
		return [];


	# Generate a list of all numbers 2 .. upperBound
	A = [True] * (upperBound - 1);

	# We only need to check up to the square root of upperBound
	upperBoundRoot = int(math.sqrt(upperBound));

	for i in xrange(2, upperBoundRoot + 1) :

		# if A[i] is prime, remove its multiples
		if (A[i - 2] == True) :
			square = math.pow(i, 2);

			# Mark all multiples of i as composite
			for j in xrange(0, int((upperBound - square) / i) + 1) :
				index = int(square + i * j);
				A[index - 2] = False;

	# Cleanup the results
	result = [];
	for element in xrange(0, len(A)) :
		if (A[element] == True) :
			result.append(element + 2);

	return result;

# Setup the connection
serverSocket = socket.socket();
# serverName = socket.gethostname();
serverPort = 21758;

serverSocket.bind(('', serverPort));

# Listen for connections
serverSocket.listen(8);

while (True) :
	
	clientSocket, clientAddress = serverSocket.accept();
	bound = int(clientSocket.recv(1024));
	clientSocket.send(str(getPrimes(bound)));
	clientSocket.close();




