# Jonathan Petersen
# A01236750
# Midterm 1
# Problem 2

# Get the month name from a two-digit month number
def getMonth(numMonth) :
	return {
		"01" : "January",
		"02" : "February",
		"03" : "March",
		"04" : "April",
		"05" : "May",
		"06" : "June",
		"07" : "July",
		"08" : "August",
		"09" : "September",
		"10" : "October",
		"11" : "November",
		"12" : "December",
	} [numMonth]

# Takes a string of format MMDDYYYY and prints a date in the form Month Day, Year
def formatDate(dateString) :

	month = getMonth(dateString[:2]);
	day = str(int(dateString[2:4])); # Convert back and forth to remove the leading 0's.
	year = dateString[-4:];

	return "{0} {1}, {2}".format(month, day, year);


# Driver Code
# print formatDate("10111947");

date = raw_input("Enter Date : ");
print formatDate(date);
