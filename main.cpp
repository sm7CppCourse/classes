#include <iostream>

#include "smart_array.h"
#include "complex.h"

int main()
{
	SmartArray<Complex> a;
	a.pushBack(Complex(1, 1));
	a.pushBack(Complex(2, 2));

	SmartArray<Complex> b(a);

	SmartArray<Complex> c;
	c = b;

	b.pushBack(Complex(3, 3));

	c.pushBack(Complex(4, 4));

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;

	getchar();
	return 0;
}
