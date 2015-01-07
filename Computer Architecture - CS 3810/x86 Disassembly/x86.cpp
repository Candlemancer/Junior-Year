// Jonathan Petersen
// A01236750
// x86 Disassembly

#include <iostream>

void whatDoIDo() {

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;

	int f = a + b + c + d + e;


	std::cout << "f: " << f << std::endl;

	return;
}

int main() {

	whatDoIDo();

	return 0;
}

