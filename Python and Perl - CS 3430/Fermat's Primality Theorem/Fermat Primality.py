# Jonathan Petersen
# A01236750
# Fermat's Primality Test Assignment

import random;
random.seed();

def isFermatPrime(number, repetitions, test = 2) :

	if (number == 1 or number == 2) :
		return True;

	if (repetitions <= 0) :
		return True;

	# This is always true if test == 1
	if (test ** number % number == test) :
		return True and isFermatPrime(number, repetitions - 1, random.randint(2, number - 1));

	return False;

# def findFermatPrimes(numbers, repetitions, test = 2) :

print isFermatPrime(9275, 20);
