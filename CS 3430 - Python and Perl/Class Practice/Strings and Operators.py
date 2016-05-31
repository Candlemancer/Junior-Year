# Jonathan Petersen
# A01236750
# Strings and Operators

# Operators
x = 56;
y = 80;

print(x + y);
print(x - y);
print(x * y);
print(x ** y);
print(x / y);
print(x // y);
print(x % y);

x, y = 34, 66;
#      ^x  ^y
x, y = y, x; # Swap


# Strings
firstName = "Gerard";
lastName = "Umulat";

#Similar to printf. Use a % and make sure the arguments are contained in ()'s
print( "My name is %s %s, and I am %d years old." % (firstName, lastName, x) );

#import string
#string.upper("Hello");
print("Explode!11!1".upper());

#string.strip("x");
print("     Chiasmatic     ".strip());


# String Buildilng
A = [ 'U', 'n', 'i', 'f', 'i', 'c', 'a', 'tion' ];

civilWar = '';

for i in A:
	civilWar += i;
print(civilWar);

laborUnion = "".join(A);
print(laborUnion);


# String function
paragraph = '''Whatever you can do,
Or dream you can, Begin it!
Boldness has Genius, Power, and Magic in it.''';

print(paragraph[9].upper() + paragraph[10:16] + ".");
print(paragraph.find("Begin"));
print(paragraph.find("Begin", paragraph.find("Begin") + 1)); # With iniPos specifier.

B = paragraph.split("\n");
print B;

p4r4gr4ph = paragraph.replace("i", "1");
p4r4gr4ph = p4r4gr4ph.replace("l", "1");
p4r4gr4ph = p4r4gr4ph.replace("a", "4");
p4r4gr4ph = p4r4gr4ph.replace("o", "0");
p4r4gr4ph = p4r4gr4ph.replace("s", "$");
p4r4gr4ph = p4r4gr4ph.replace("e", "3");
p4r4gr4ph = p4r4gr4ph.replace(" ", "");
print p4r4gr4ph;

