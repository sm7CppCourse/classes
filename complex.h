
#include <cmath>
#include <istream>
#include <ostream>

/*
Класс Complex, описывающий комплексное число.
*/
class Complex
{
private:
	double real;
	double im;

public:
	// Статическое поле. 
	// Существует в единственном экземпляре для всех объектов класса. Память под него выделяется один раз.
	// Статическое поле можно рассматривать как глобальную переменную в пространстве имен класса.
	static const Complex WonderfulPoint;

	// Статическая функция. 
	// Ее можно рассматривать как глобальную функцию в пространстве имен класса.
	// Не принимает указатель this.
	static double norm(const Complex& c) { return sqrt(c.real*c.real + c.im*c.im); }

public:
	// Конструктор класса. Вызывается один раз при инициализации класса.
	Complex(double r = 0, double i = 0) 
		: real(r), im(i)  // <- список инициализаторов. 
	{
	}

	// Конструктор копирования.
	// Вызывается в тех случаях, когда новый объект создается путем копирования существующего.
	// В случае класса Complex можно опустить, т.к. по умолчанию конструктор копирования в любом классе 
	// реализован как поэлементное копирование полей класса.
	Complex(const Complex &b) : real(b.real), im(b.im)
	{
	}

	// Деструктор класса. 
	// Вызывается автоматически когда объект класса выходит из области видимости.
	// В основном используется для освобождения ресурсов, занятых объектом класса: динамической памяти, файлов и т.д.
    // В случае класса Complex можно опустить, т.к. по умолчанию в любом классе создается пустой деструктор.
	~Complex()
	{
	}

	// Перегрузка оператора присваивания.
	// Вызывается каждый раз когда одному существующему объекту присваивается значение другого.
	// В случае класса Complex можно опустить, т.к. по умолчанию операция присваивания в любом классе 
	// реализована как поэлементное копирование полей класса.
	Complex& operator=(const Complex &);
	
	// Перегрузка операторов приведения типа.
	// В данном случае указывает каким образом производится преобразование из типа Complex в тип double.
	// В тех случаях когда не определена какая либо операция или функция для объектов 
	// класса Complex, но определена для переменных типа double, компилятор сначала 
	// выполнит преобразование из Complex в double.
    //operator double() const { return real; } 

	// Перегрузка оператора индексирования.
	double operator[] (int) const;

	// Перегрузка бинарных операторов.
	// Вызвавший функцию-операцию объект считается первым операндом.
	Complex operator+(const Complex &) const;
	Complex operator-(const Complex &) const;

	Complex operator*(double) const;
	Complex operator/(double) const;

	Complex operator*(const Complex &) const;
	Complex operator/(const Complex &) const;

	Complex& operator+=(const Complex &b) { return *this = *this + b; }
	Complex& operator-=(const Complex &b) { return *this = *this - b; }

	Complex& operator*=(double k) { return *this = *this * k; }
	Complex& operator/=(double k) { return *this = *this / k; }

	Complex& operator*=(const Complex &b) { return *this = *this * b; }
	Complex& operator/=(const Complex &b) { return *this = *this / b; }

	bool operator==(const Complex &b) const { return real == b.real && im == b.im; }
	bool operator!=(const Complex &b) const { return !(*this == b); }
	bool operator> (const Complex &b) const;
	bool operator< (const Complex &b) const;

	// Дружественные функции. Не являются членами класса, но имеют доступ к его закрытым членам.
	// В данном случае дружественными объявлены функции ввода/вывода в консоль.
	friend std::ostream& operator<<(std::ostream& o, const Complex& c);
	friend std::istream& operator>>(std::istream& o, Complex& c);
};

// Перегрузка бинарных операторов.
// Объявлены вне класса, не получают указатель this. 
// В списке параметров должны быть явно указаны оба операнда.
Complex operator*(double, const Complex&);
Complex operator/(double, const Complex&);




