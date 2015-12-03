#include <iostream>

#include "smart_array.h"
#include "matrix.h"
#include "complex.h"

int main()
{
	// Smart array tests
	std::cout << "Smart array tests\n";
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
	
	// Matrix tests	
	std::cout << "Matrix tests\n";	
	Matrix <int> m1(2,3); 
	m1 << 1, 1, 1, 
	      2, 2, 2;

	std::cout << "m1 = \n" << m1 << "\n";

	Matrix <int> m2(3,4); 
	m2 << 1, 2, 3, 4, 
   	      1, 2, 3, 4,
  	      1, 2, 3, 4;

	std::cout << "m2 = \n" << m2 << "\n";

	Matrix <int> m3 = m1*m2;

	std::cout << "m1*m2 = \n" << m3 << "\n";	

	getchar();
	return 0;
}
