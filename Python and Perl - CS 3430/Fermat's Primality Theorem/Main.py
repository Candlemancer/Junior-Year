# Jonathan Petersen
# A01236750
# Fermat Primality Testing Assignment
# Driver Code

import FermatPrimality;

# Assignemnt Requirements
print FermatPrimality.isFermatPrime(1, 20);
print FermatPrimality.findFermatPrimes([1, 2, 3, 4, 5, 6, 7, 8, 9], 20);

# Upper bound on the second function.
A = range(1, 979);
print FermatPrimality.findFermatPrimes(A, 20);
