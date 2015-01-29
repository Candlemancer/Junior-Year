# Jonathan Petersen
# A01236750
# Fermat's Primality Test Assignment

import sys;
import random;
random.seed();

# Test whether or not a number is time. Note that this test is necessary but not sufficient to prove
# primality, since there are numbers that will always fool this test.
def isFermatPrime(number, repetitions, test = 2) :

	if (number == 1 or number == 2) :
		return True;

	if (repetitions <= 0) :
		return True;

	# This is always true if test == 1
	if (test ** number % number == test) :
		return True and isFermatPrime(number, repetitions - 1, random.randint(2, number - 1));

	return False;

# Find primes in a list of numbers using the Fermat primality test.
# NOTE: This function must be recursive due to assignment constraints, but since Python doesn't
#   implement tail recursion this function only natively supports lists of size <= 979
def findFermatPrimes(numbers, repetitions, test = 2) :

	if (len(numbers) == 0) :
		return [];

	currentNumber = numbers.pop();

	if (isFermatPrime(currentNumber, repetitions, test)) :
		return ( findFermatPrimes(numbers, repetitions, test) + [currentNumber] );

	return findFermatPrimes(numbers, repetitions, test);


