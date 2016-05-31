# Jonathan Petersen
# A01236750
# Final Project 
# Matrix Class

import numbers;
import itertools;
from fractions import gcd;

class Matrix :


	def __init__(self, rows, cols, data, exchanges = 0) :
		
		self.numRows = rows;
		self.numCols = cols;
		self.matrix = [];

		self.rowSwaps = exchanges;

		# "Copy Constructor"
		if (isinstance(data, Matrix)) :
			# self.numRows = data.numRows;
			# self.numCols = data.numCols;
			self.matrix.extend(data.matrix);
			return;

		# "Parameter Constructor"
		for i in range(0, rows):

			tempRow = [];

			for j in range(0, cols):
				tempRow.insert(0, data.pop());

			self.matrix.insert(0, tempRow);

		return;

	def transpose(self) :

		toReturn = [];
		for i in xrange(0, self.numCols):

			for j in xrange(0, self.numRows):
				toReturn.append(self.matrix[j][i]);

		return Matrix(self.numCols, self.numRows, toReturn);

	def diagonalize(self) : 

		toReturn = [];
		toReturn.extend(self.rref().matrix);

		for i in range(self.numCols - 1, -1, -1) :
			for j in range(i - 1, -1, -1) :
				# print "i: " + str(i) + " j: " + str(j);
				toReturn[j] = self.reduceRow(i, i, j, toReturn)

		toReturn = itertools.chain(*toReturn);
		return Matrix(len(self.matrix), len(self.matrix[0]), list(toReturn), self.rowSwaps);	

	def rref(self) :
		
		toReturn = [];
		toReturn.extend(self.matrix);

		for i in range(0, self.numCols) :
			for j in range(i + 1, self.numRows) :
				toReturn[j] = self.reduceRow(i, i, j, toReturn);

		toReturn = itertools.chain(*toReturn);
		return Matrix(len(self.matrix), len(self.matrix[0]), list(toReturn), self.rowSwaps);		

	def reduceRow(self, idx_column, idx_base, idx_toReduce, mat) :

		toReturn = [];

		# If the current pivot is 0
		if (mat[idx_base][idx_column] == 0) :

			# and if the row below has a nonzero leading term in this column
			if (idx_base < self.numRows) and (idx_base < idx_toReduce) :
				if (mat[idx_base + 1][idx_column] != 0) :
					# then swap rows
					temp = mat[idx_base]
					mat[idx_base] = mat[idx_base + 1]
					mat[idx_base + 1] = temp;
					self.rowSwaps += 1;

			reductionFactor = 0;
		elif (mat[idx_toReduce][idx_column] % mat[idx_base][idx_column] == 0) :
			reductionFactor = mat[idx_toReduce][idx_column] / mat[idx_base][idx_column];
		else :
			mat[idx_toReduce] = [i * mat[idx_base][idx_column] for i in mat[idx_toReduce]]
			reductionFactor = mat[idx_toReduce][idx_column] / mat[idx_base][idx_column];

		tempRow = [ i * reductionFactor for i in mat[idx_base] ]
		toReturn = [ mat[idx_toReduce][i] - tempRow[i] for
				   i in range(0, len(tempRow)) ];

		return toReturn;

	def getPivots(self) :
		self.pivots = [];

		# reduced = self.rref();
		for i in range(0, len(self.matrix)) :
			self.pivots.append(self.matrix[i][i]);

		return self.pivots;

	def getDeterminant(self) :
		
		# Make sure the matrix is square
		assert (self.numRows == self.numCols), "Cannot compute determinant of a non-square matrix!"

		# Compute the sign based on row exchanges
		sign = 1;
		if (self.rowSwaps % 2 != 0) :
			sign = -1;

		# Compute the product of the pivots
		self.determinant = sign;
		for i in self.rref().getPivots() :
			self.determinant *= i;

		return self.determinant;

	def simplifyDiagonal(self) :

		# A small matrix is already simple
		if self.numRows <= 1 or self.numCols <= 1 :
			return Matrix(self.numRows, self.numCols, self);

		# Otherwise find the GCD of all the diagonals
		totalGCD = gcd(self.matrix[0][0], self.matrix[1][1]);
		for i in range(1, self.numRows) :
			totalGCD = gcd(totalGCD, self.matrix[i][i]);

		return Matrix(self.numRows, self.numCols, self * (1.0 / totalGCD));

	def invert(self) :
		
		# assert self.getDeterminant() != 0, "Cannot invert a matrix with determinant of zero!";

		identity = self.makeIdentity(self.numRows);
		
		reduced = Matrix(self.numRows, self.numCols * 2, self);
		for i in reduced.matrix :
			i.extend(identity.matrix.pop(0));

		reduced = reduced.rref();
		reduced.numCols /=2;
		reduced = reduced.diagonalize();

		inverse = [ i[self.numRows:] for i in reduced.matrix ]
		for i in range(0, len(inverse)) :
			for j in range(0, len(inverse[0])) :
				inverse[i][j] /= (reduced.matrix[i][i] * 1.0);

		self.matrix = [ i[:self.numRows] for i  in self.matrix ]
		toReturn = itertools.chain(*inverse);
		return Matrix(len(inverse), len(inverse[0]), list(toReturn));

	def makeIdentity(self, size) :

		toReturn = [];

		for i in range(0, size) :
			for j in range(0, size) :
				if i == j :
					toReturn.append(1);
				else :
					toReturn.append(0);

		return Matrix(size, size, toReturn);

	def __add__(self, other) :

		# Make sure we're adding two Matrices
		if not isinstance(other, Matrix) :
			raise TypeError('unsupported operand types for +');

		# And that they're the same size
		assert ((self.numCols == other.numCols) and (self.numRows == other.numRows)), 'Matrix.__add__: operand self has different dimension than operand other';

		toReturn = [];
		for i in xrange(0, self.numRows):

			for j in xrange(0, self.numCols):
				toReturn.append(self.matrix[i][j] + other.matrix[i][j]);

		return Matrix(self.numRows, self.numCols, toReturn);

	def __radd__(self, other) :
		return self.__add__(other);

	def __sub__(self, other) :

		# Make sure we're adding two Matrices
		if not isinstance(other, Matrix) :
			raise TypeError('unsupported operand types for +');

		# And that they're the same size
		assert ((self.numCols == other.numCols) and (self.numRows == other.numRows)), 'Matrix.__add__: operand self has different dimension than operand other';

		toReturn = [];
		for i in xrange(0, self.numRows):

			for j in xrange(0, self.numCols):
				toReturn.append(self.matrix[i][j] - other.matrix[i][j]);

		return Matrix(self.numRows, self.numCols, toReturn);

	def __rsub__(self, other) :
		return self.__sub__(other);

	def __str__(self) :
		return "[" + ', \n '.join(str(x) for x in self.matrix) + "]";

	def __mul__(self, other) :
		
		if isinstance(other, numbers.Number) : 

			toReturn = [];
			for i in xrange(0, self.numRows):

				for j in xrange(0, self.numCols):
					toReturn.append(self.matrix[i][j] * other);

			return Matrix(self.numRows, self.numCols, toReturn);

		if isinstance(other, Matrix) :

			assert (self.numCols == other.numRows), 'Matrix.__mul__: operand self has different dimension than operand right transpose';

			tempRow = [0] * other.numCols;
			toReturn = [tempRow] * self.numRows;

			# print toReturn
			# print self.matrix, other.matrix

			for i in xrange(0, self.numRows):

				for j in xrange(0, other.numCols):

					tempSum = 0;

					for k in range(0, len(self.matrix[i])) :

						# print k, ": ", self.matrix[i], ", ", other.transpose().matrix[j]
						# print self.matrix[i][k], " * ", other.transpose().matrix[j][k]
						# print "------------"

						tempSum =+ (self.matrix[i][k] * other.transpose().matrix[j][k]);

					toReturn[i][j] = tempSum;

			toReturn = itertools.chain(*toReturn)
			return Matrix(self.numRows, other.numCols, list(toReturn));

	def __rmul__(self, other) :
		return self.__mul__(other);
		
# //////////////////////////////////////////////////////////////////////////////////////////////// #

a = Matrix(2, 2, [1, 2, 3, 4]);
b = Matrix(3, 3, range(1, 10));
c = Matrix(2, 2, [2, 3, 4, 5]);
d = a + c;
e = Matrix(2, 3, [2, 2, 3, 4, 5, 6]);
f = Matrix(3, 2, [1, 8, 7, 6, 5, 4]);
h = Matrix(3, 3, [1, -1, 0, -1, 2, -1, 0, -1, 2]);
i = Matrix(3, 3, [1, 2, 2, 4, 8, 9, 0, 3, 2]);
j = Matrix(3, 3, [1, 0, 0, -1, 1, 0, 0, -1, 1]);
k = Matrix(5, 5, 
	[3, 0, 0, 0, 0,
	 2,-6, 0, 0, 0,
	17,14, 2, 0, 0,
	22,-2,15, 8, 0,
	43,12, 1,-1, 5]);
l = Matrix(3, 3, [2, 0, 1, 0, 2, 0, 1, 0, 2]);
m = Matrix(2, 2, [2, 1, 1, 2]);
n = Matrix(2, 2, [1, 2, 2, 4]);
o = Matrix(1, 3, [1, 2, 3]);
p = Matrix(3, 1, [2, 2, 2]);



# Other Tests
# print a
# print b;
# print c;
# print d;
# print b;
# print b.transpose();
# g = e.transpose();
# print e;
# print f;
# print f.transpose();
# print e + f.transpose();
# print e * g;
# print e;
# print e.rref();
# print "-----------------------"
# print
# print b
# print b.rref();
# print "-----------------------"
# print
# print h;
# print
# print h.diagonalize();
# print 
# print h.getDeterminant();
# print "-----------------------"
# print
# print i
# print 
# print i.rref();
# print 
# print i.diagonalize();
# print
# print i.invert() * 3;
# print
# print i.getDeterminant();
# print 
# print i;
# print
# print i.rref().diagonalize().invert() * 3;
# print
# print i;
# print e.getDeterminant();
# i.invert();
# print j;
# print j.invert();
# print k;
# print k.invert();
# print l;
# print l.getEigenvalues();
# print m;
# print m.rref();
# print m.diagonalize().simplifyDiagonal();
# print m.getEigenvalues();
# print n;
# print n.diagonalize();
# print n.combinePolynomials([1, 1], [1, -1])
# print n.combinePolynomials([1, 2, 1], [1, 2]);
# print n.combinePolynomials([1, 2], [1, 2, 1]);
# print n.getEigenvalues();
# print m - n;
# print m + n;
# print m * n;
# print m / n;
# print o;
# print p;
# print o * p;
# print p * o;
# print m * n;
# print f * e;
