#!/usr/bin/perl

# Jonathan Petersen
# A01236750
# Midterm 2
# Problem 1

use warnings;

# Recall that a prime number is a natural number greater than 1 that is divisible by 1 and itself. 
# The 1st prime number is 2. The 2nd prime number is 3. The 3rd prime number is 5, etc. The list of 
# the first 500 primes is given here. Write a Perl script that prompts the user for an integer i and
# computes the i-th prime. Use your script to compute the 20,005-th prime. Your script must have 
# strict identifier scoping, i.e. all identifiers must have explicit scope declarations.

# Subroutine to compute the i-th prime.
sub getPrimes {
	my $index = $_[0];
	my @primes = (2, 3);

	if ($index == 1) { return 2; }

	# For each number that could be a prime
	for (my $currentNumber = $primes[-1] + 2; scalar @primes < $index; $currentNumber += 2) {

		print $currentNumber . "\n";

		my $primeIndex = 0;
		my $isPrime = 1;
		for (my $divisor = 2; $divisor <= sqrt($index); $divisor = $primes[$primeIndex]) {

			if ($currentNumber % $divisor == 0) { $isPrime = 0; last; }

			$primeIndex += 1;
		}

		if ($isPrime == 1) {
			push(@primes, $currentNumber);
		}

	}

	return $primes[-1];
}



# Subroutine to get an integer from the user.
sub getInteger {
	print "Please enter an integer: ";
	my $integer = <STDIN>;
	chomp $integer;

	return $integer;
}

print " : " . getPrimes(8) . "\n";
