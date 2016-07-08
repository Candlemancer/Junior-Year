#!/usr/bin/perl

# Jonathan Petersen
# A01236750
# Midterm 2
# Problem 3

# Write a perl script to print out stars in a specific pattern, such that the first line has one 
# star, the second has three stars, the third has five stars, etc. All stars should be printed in a 
# triangle with the middle star centered and one space of whitespace between each column.

# e.g.  *
#     * * *
#   * * * * *
# * * * * * * *

sub printStars {

	my $numLines = $_[0];

	for (my $i = 0; $i < $numLines; $i++) {
		# print $i + 1;
		# print "\n";

		print "  " x ($numLines - $i);
		print "* " x ($i + 1);
		print "* " x ($i);
		print "  " x ($numLines - $i);
		print "\n";
	}

}

printStars(5);
