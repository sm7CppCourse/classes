#include <iostream>   // std::ostream, std::istream
#include <stdexcept>  // std::out_of_range

template <typename TValue> 
class Matrix
{
private:
	TValue* data_;
	int		rows_;
	int		cols_;

public:
	// Конструктор по умолчанию. Создает пустую матрицу.
	Matrix () 
		: rows_(0), cols_(0), data_(0)
	{
	}

	// Конструктор, принимающий количество столбцов, строк и, возможно, указатель на начальные данные
	Matrix (int rows, int cols = 0, const TValue* src = 0) 
	{
		// Выделение динамической памяти и копирование данных
		mem_alloc(rows, cols);
		mem_copy(src);
	}

	// Конструктор копирования.
	// Важно! По умолчанию будет создан конструктор копирования, выполняющий поэлементное копирование полей.
	// Для класса SmartArray это означает, что выделенная памть может быть очищена дважды, что приведет к ошибке.
	Matrix(const Matrix& src)
	{
		// Выделение динамической памяти и копирование данных
		mem_alloc(src.rows_, src.cols_);
		mem_copy(src.data_);
	}

	// Статическая функция. Возвращает единичную матрицу
	static Matrix Identity(int rows, int cols = 0)
	{
		Matrix result(rows, cols);

		int n = std::min(result.getRows(), result.getCols());
		for(int i=0; i<n; ++i) {
			result(i,i) = TValue(1.0);
		}

		return result;
	}

	// Деструктор. Освобождаем память.
	~Matrix ()
	{
		mem_free();
	}

	// Возвращает количество строк
	int getRows() const
	{
		return rows_;
	}

	// Возвращает количество столбцов
	int getCols() const
	{
		return cols_;
	}

	// Перегрузка оператора индексации ().
	// В данном случае реализуем логику возвращения указателя на строку матрицы.
	// Пример использования:
	// Matrix<double> m(2,2);  
	// double* row = m[1];  
	// double item = m[1][1]; // <- проверка на выход индекса столбца за границы матрицы не производится!
	TValue* operator [] (unsigned i) const
	{
		if(i<rows_) {
			return data_ + i*cols_;
		}

		throw std::out_of_range("Bad row index");
	}

	// Перегрузка оператора вызова функции ().
	// В данном случае реализуем логику возвращения элемента матрицы с проверкой 
	// выхода индексов за границы матрицы.
	TValue& operator () (unsigned i, unsigned j) const
	{
		if(i<rows_ && j<cols_) {
			return data_[i*cols_ + j];
		}

		throw std::out_of_range("Bad row or column index");
	}

	// Перегрузка оператора присваивания.
	// Важно! По умолчанию будет реализована операция присваивания, выполняющая поэлементное копирование полей.
	// Для класса Matrix это означает, что выделенная памть может быть очищена дважды, что приведет к ошибке.
	Matrix& operator = (const Matrix& src)
	{
		if(&src != this) // Проверка на самоприсваивание
		{
			// Освобождение ранее выделенного блока памяти
			mem_free();									

			// Выделение динамической памяти и копирование данных
			mem_alloc(src.rows_, src.cols_);	
			mem_copy(src.data_);
		}

		return *this;
	}

	// Перегрузка оператора *. Реализует операцию умножение матриц
	Matrix operator * (const Matrix& b) const
	{
		if (cols_ != b.rows_)
			throw std::logic_error("Dimensions of the matrices are not consistent");

		Matrix result(rows_, b.cols_);

		for (int i=0; i<rows_; i++)
		{
			for (int j=0; j<b.cols_; j++)
			{
				for (int k=0; k<cols_; k++)
				{
					result(i,j) += (*this)(i,k) * b(k,j); 
				}
			}
		}

		return result;
	}

	//Вспомогательный класс для задания значений элементов матрицы
	class Setter
	{
		TValue* ptr_;
		TValue* end_;

	public:
		Setter(TValue* ptr, int length) : ptr_(ptr), end_(ptr+length)
		{
		}
		
		// Перегрузка оператора запятая (да, так тоже можно).
		// Устанавливает очередной элемент матрицы.
		// Пример работы:
		//   Matrix<double> m(2,2);
		//   m << 1, 2, 3, 4;
		// Матрица m примет вид:
		//   | 1 2 |
		//   | 3 4 |
		Setter& operator , (TValue val)
		{
			if(ptr_ > end_)
				throw std::out_of_range("So many values");

			*(ptr_++) = val;

			return *this;
		}
	};

	// Перегрузка оператора <<. 
	// Возвращает объект, позволяющий в удобной форме задать значения элементов матрицы.
	Setter operator << (TValue val)
	{
		return (Setter(data_, rows_*cols_) , val);
	}

private:
	// Скрытые функции, отвечающие за внутреннюю логику работы класса.
	
	// Выделение памяти
	void mem_alloc(int rows, int cols)
	{
		if(cols == 0) {						 // Если один из индексов не задан, считаем матрицу квадратной
			cols = rows;
		}

		data_ = new TValue[rows*cols];		 // Выделение динамической памяти для хранения элементов матрицы
		rows_ = rows;						 // Установка количества строк и столбцов 
		cols_ = cols;
	}

	// Заполнение матрицы памяти
	void mem_copy(const TValue* src)
	{
		if(rows_ > 0 && cols_ > 0)
		{
			if(src)
			{
				for (int i=0; i<rows_*cols_; i++) {
					data_[i] = src[i];		 // Копирование элементов переданной матрицы
				}
			}
			else
			{
				for (int i=0; i<rows_*cols_; i++) {
					data_[i] = TValue();     // Заполнение матрицы нулевыми элементами
				}
			}
		}
	}

	// Освобождение памяти
	void mem_free()
	{
		delete [] data_;					// Освобождение ранее выделенного блока памяти
		data_ = 0;
		rows_ = cols_ = 0;
	}
};


// Переопределение оператора << класса std::ostream для вывода на консоль элементов матрицы Matrix
template<class TValue>
std::ostream& operator<<(std::ostream& o, const Matrix<TValue>& m)
{
	if( m.getCols() <= 0 || m.getRows() <= 0)
	{
		return o << "[]\n";
	}

	for (int i=0; i<m.getRows(); i++)
	{
		o << "|" << m(i,0);
		for(int j=1; j<m.getCols(); ++j)
		{ 
			o << ", " << m(i,j); 
		}
		o << "|\n";
	}

	return o;
}
