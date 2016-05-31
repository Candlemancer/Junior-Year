# Jonathan Petersen
# A01236750
# Newton Raphson Approximation

def myFun(x) :
	return x ** 3 - 2 * x - 5;

def myFunPrime(x) :
	return 3 * x ** 2 - 2;

def yourFun(x) :
	return x ** 6 - 2;

def yourFunPrime(x) :
	return 6 * x ** 5;

def newtonRaphsonApproximation(guess, function, derivativeFunction, lastGuess = 0) :

	if(guess == lastGuess or
	   guess >= 100000000 or
	   guess <= -10000000) :
		# print guess;
		return guess;

	# print (str(guess) + "\r ");


	return newtonRaphsonApproximation(
		guess - (function(guess) / derivativeFunction(guess)),  # <- x0 - f(x) / f'(x) for next guess
		function,
		derivativeFunction,
		guess);

print newtonRaphsonApproximation(2.0, myFun, myFunPrime);
print newtonRaphsonApproximation(1.0, yourFun, yourFunPrime);
