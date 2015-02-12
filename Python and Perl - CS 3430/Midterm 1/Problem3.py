# Jonathan Petersen
# A01236750
# Midterm 1
# Problem 3

import string;
import random;

# Generate random passwords with the following structure: (one capital letter, followed by six
# small letters, followed by one number)
def generatePassword() :

	upperCase = random.choice(string.ascii_uppercase);

	lowerCase = random.sample(string.ascii_lowercase, 6);
	random.shuffle(lowerCase);
	lowerCase = ''.join(lowerCase);

	digit = random.choice(string.digits);

	return upperCase + lowerCase + digit;

# Driver Code
for i in range(5) :
	print "(\'Password{0}\', \'{1}\')".format(i + 1, generatePassword());

# passwords = { "Password" + str(i) : generatePassword() for i in range(5) }

