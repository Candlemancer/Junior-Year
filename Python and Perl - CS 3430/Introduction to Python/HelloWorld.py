# Jonathan Petersen
# A01236750
# Hello World Program
# And Other Python Basics

print "Hello World";
print 1+2;
#'s are comments

# Boolean Types
x = False;
print bool(x);
print bool(4);

A = [];
print bool(A);

# Casting using factories.
number = int('59');
print number;
string = "12";
number = int(string);
print number;

# Lists and other Containers
# A is a list
print len(A);
A.append(x);
A.append(number);
A.append(string);
A.append(A);

# A-ception
for i in A:
	print i;
	for j in A[3]:
		print j;
