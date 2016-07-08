#!/usr/bin/perl

# Jonathan Petersen
# A01236750
# Midterm 2
# Problem 2

use warnings;

# Take an integer from the user and determine if the input is a palindrome.

# Subroutine to check if a provided string is an integer.
sub palindrome {
	my @args = @_;

	my $len = length $args[0];
	my $isPalindrome = 1;

	for (my $i = 0; $i < int($len / 2); $i++) {

		my $head = substr($args[0], $i, 1);
		my $tail = substr($args[0], ($len - 1) - $i, 1);

		# Check if each character is equal to its mirror character, 
		# and if no other pairs have failed.
		if ($head != $tail or $isPalindrome != 1) { $isPalindrome = 0; }
	}

	return $isPalindrome;
}


# Subroutine to get an integer from the user.
sub getInteger {
	print "Please enter an integer: ";
	my $integer = <STDIN>;
	chomp $integer;

	return $integer;
}


# Driver Code
my $value = getInteger();
if (palindrome($value)) {
	print "The number was a palindrome!\n";
}
else {
	print "The number is not a palindrome.\n";
}

