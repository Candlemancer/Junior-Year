#!/usr/bin/perl -W

# Jonathan Petersen
# A01236750

use warnings;

# Hello World!
print "Hello World!\n";

# Single quoted strings aren't interpolated
print 'Please enter a number\n' . "\n";

# Define two scalars with $
$num1 = 14;
$num2 = <STDIN>;

# Remove the \n at the end
chomp $num2;

# Print out the sum of the two numbers.
$sum = $num1 + $num2;
# Print two newlines
print $sum . "\n" x 2;
