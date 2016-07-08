#!/usr/bin/perl -W

# Jonathan Petersen
# A01236750
# Scalar Arithmetic Assignment
# Sum of 3's and 5's Script

use warnings;

# Read in a number.
print "Please enter a number greater than 0: ";
$number = <STDIN>;
chomp $number;

# Find the multiples of 3 and 5 that are less than that number.
$total = 0;
for (my $i = 0; $i < $number; $i++) {
	if ($i % 3 == 0) {
		$total += $i;
	}
	if ($i % 5 == 0) {
		$total += $i;
	}
}

# Print out the results
print "The sum of all numbers which are multiples of 3 or 5 less than ",
	$number, " is ", $total, ".\n";
