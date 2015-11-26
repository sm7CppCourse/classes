#include <iostream>   // std::ostream, std::istream
#include <stdexcept>  // std::out_of_range
#include "complex.h"


// Определение статического поля класса Complex (объявление внутри класса).
// Статическое поле можно рассматривать как глобальную переменную в пространстве имен класса.
const Complex Complex::WonderfulPoint(-1, 0);

Complex& Complex::operator=(const Complex &b) 
{
	this->real = b.real; 
	this->im = b.im; 
	return *this;
}

Complex Complex::operator+(const Complex &b) const
{
	return Complex(real +  b.real, im + b.im);
}

Complex Complex::operator-(const Complex &b) const
{
	return Complex(real -  b.real, im - b.im);
}

Complex Complex::operator*(double k) const
{
	return Complex(real * k, im * k);
}

Complex Complex::operator/(double k) const
{
	return Complex(real / k, im / k);
}

Complex operator*(double k, const Complex& c)
{
	return c * k;
}

Complex operator/(double k, const Complex& c)
{
	return Complex(k) / c;
}

Complex Complex::operator*(const Complex &b) const
{
    Complex c;
    c.real = real*b.real - im*b.im;
    c.im   = im*b.real + real*b.im;
    return c;
}

Complex Complex::operator/(const Complex &b) const
{
	return *this * Complex(b.real, -b.im) / (b.real*b.real + b.im*b.im);
}

bool Complex::operator> (const Complex &b) const
{
	return (real*real + im*im) > (b.real*b.real + b.im*b.im);
}

bool Complex::operator< (const Complex &b) const
{
	return !(*this > b) && *this != b;
}

double Complex::operator[] (int i) const
{
	if(i == 0) return real;
	if(i == 1) return im;

	throw std::out_of_range("Complex index.");
}

std::ostream& operator<<(std::ostream& o, const Complex& c)
{
	return o << "(" << c.real << ", " << c.im << ")";
}

std::istream& operator>>(std::istream& i, Complex& c)
{
	i >> c.real;
	i >> c.im;
	return i;
}
