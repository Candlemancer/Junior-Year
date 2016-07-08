#!/usr/bin/perl -W

# Jonathan Petersen
# A01236750
# Scalar Arithmetic Assignment
# Factors Less Than 20 Script

use warnings;


# Continue until a number is found THIS TAKES A WHILE, PS. Make a cup of coffee.
for (my $number = 2; checkFactors($number) != 0; $number++) {}

print "The smallest number with divisors [1, 20] is ", $number, ".\n";

sub checkFactors {
	$number = @_[0];

	if ($number % 2  == 0 &&
		$number % 3  == 0 &&
		$number % 4  == 0 &&
		$number % 5  == 0 &&
		$number % 6  == 0 &&
		$number % 7  == 0 &&
		$number % 8  == 0 &&
		$number % 9  == 0 &&
		$number % 10 == 0 &&
		$number % 11 == 0 &&
		$number % 12 == 0 &&
		$number % 13 == 0 &&
		$number % 14 == 0 &&
		$number % 15 == 0 &&
		$number % 16 == 0 &&
		$number % 17 == 0 &&
		$number % 18 == 0 &&
		$number % 19 == 0 &&
		$number % 20 == 0 ) {
		return 0;
	}
	else { 
		return -1; 
	}
}
