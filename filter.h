#include <math.h>

// Базовый абстрактный класс фильтра данных
class Filter 
{
	// Каждый фильтр имеет идентификатор 
	std::string name_;

public:

	// Конструктор, принимающий идентификатор
	Filter(const std::string& name) : name_(name)
	{
	}

	// Деструктор. 
	// Делаем его виртуальным, чтобы вызывался деструктор производного класса 
	// даже при удалении через указатель на базовый класс.
	// Общее правило: если класс содержит хотя бы один виртуальный метод, то 
	// деструктор следует также объявлять виртуальным.
	virtual ~Filter()
	{
	}

	// Метод, который должен реализовывать основную функциональность фильта - преобразование данных.
	// Объявлен как чисто виртальный метод. Конкретная реализация будет определена в производных классах.
	virtual double process(double step, double in) = 0;
};

// Класс, реализующий рассчет производной производной сигнала.
// Наследуется от базового класса Filter
class Derive: public Filter
{
	double prev_val_;

public:

	Derive() 
		: Filter("Derive filter")
		, prev_val_(std::numeric_limits<double>::quiet_NaN())
	{
	}

	virtual double process(double step, double in_val)
	{
		double prev_val = prev_val_;
		prev_val_ = in_val;
		return prev_val != prev_val ? 0.0 : (in_val - prev_val) / step;
	}
};

// Класс, реализующий масштабирование сигнала.
// Наследуется от базового класса Filter
class Mult: public Filter
{
	double coeff_;

public:

	Mult(double coeff) 
		: Filter("Mult filter")
		, coeff_(coeff)
	{
	}

	virtual double process(double step, double in_val)
	{
		return in_val * coeff_;
	}
};

// Класс, реализующий интегрирование сигнала.
// Наследуется от базового класса Filter
class Integrate: public Filter
{
	double value_;

public:

	Integrate(double start_val) 
		: Filter("Integrate filter")
		, value_(start_val)
	{
	}

	virtual double process(double step, double in_val)
	{
		return value_ += in_val * step;
	}
};

// Класс, реализующий сдвиг сигнала.
// Наследуется от базового класса Filter
class Bias: public Filter
{
	double bias_;

public:

	Bias(double bias) 
		: Filter("Bias filter")
		, bias_(bias)
	{
	}

	virtual double process(double step, double in_val)
	{
		return in_val + bias_;
	}
};
