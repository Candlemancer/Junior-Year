# Jonathan Petersen
# A01236750
# Midterm 1
# Problem 1

# Compute and display the sum of the numbers from N to (2 * N) if N is nonnegative. If N is a
# negative number, then it's the sum of the numbers from (2 * N) to N. The starting and ending
# points are included in the sum.
def computePartialSum(number) :

	lowerbound = number;
	upperbound = number * 2;

	if ( number < 0 ) :
		lowerbound = number * 2;
		upperbound = number;

	# Since the range is inclusive, we need to convert from [l,u) to [l, u] by adding 1 to u.
	A = range(lowerbound, upperbound + 1);
	return "Sum : " + str(sum(A));


# Driver Code
# print computePartialSum(5);
# print computePartialSum(-4);
# print computePartialSum(0);

# Get a number from the user
number = int(raw_input("Enter Number : "));
print computePartialSum(number);
