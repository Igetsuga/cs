// Сиразетдинов Рустем КМБО-01-21 Вариант 24

#include <random>
#include <string>

#include <iomanip>
#include <iostream>
#include <fstream>

#define watch(variable) std::cout  << "Matix: " << (#variable)


class Exception : public std::exception
{
protected:
	
	// std::string* message_;
	char* message_;    // error message
public:

	Exception()
	{
		message_ = nullptr;
	}


	Exception(const char* message)
	{

		message_ = new char[strlen(message) + 1];   // strlen(С-string) <=> string::message.size();	
		strcpy_s(message_, strlen(message) + 1, message);   // method from C, idk, better to use methods with `string`
	}

	// constructor_copy
	Exception(const Exception &exception)  
	{
		message_ = new char[strlen(exception.message_) + 1];
		strcpy_s(message_, strlen(exception.message_) + 1, exception.message_);
	}

	// destructor
	~Exception()
	{
		delete[] message_; message_ = nullptr;
	}

	virtual void print()
	{
		std::cout  << '\n' << "{Exception}: " << message_ << "; " << std::exception::what();
	}
};

class IndexOutOfBounds : public Exception
{
protected:
	int index_row_; int index_column_;
public:

	// constructor_full
	IndexOutOfBounds(const char* message, const int &index_row, const int &index_column) : Exception(message)
	{
		index_row_ = index_row; index_column_ = index_column;
	}

	// constructor_copy
	IndexOutOfBounds(const IndexOutOfBounds &exeption)
	{
		message_ = new char[strlen(exeption.message_) + 1];
		strcpy_s(message_, strlen(exeption.message_) + 1, exeption.message_);
		index_row_ = exeption.index_row_; index_column_ = exeption.index_column_;
	}

	// destructor
	~IndexOutOfBounds() {}

	virtual void print()
	{
		std::cout  << '\n' <<  message_ << ": " << "it is not possible to access the specified indexes: row- " << index_row_
		<< " ,column- " << index_column_ << '!';
	}
};

class WrongDimension : public  Exception
{
public:
	// constructor
	WrongDimension(const char* message) : Exception(message) {}

	// destructor
	~WrongDimension() {}

};

class WrongSize : public WrongDimension
{
private:
	int index_row_; int index_column_;
	int index_row_other_; int index_column_other_;
public:
	WrongSize(const char *message, const int &index_row, const int &index_column, const int &index_row_other, const int &index_column_other) : WrongDimension(message)
	{
		index_row_ = index_row; index_column_ = index_column;
		index_row_other_ = index_row_other; index_column_other_ = index_column_other;
	}

	~WrongSize() {}

	virtual void print()
	{
		std::cout  << '\n' << "{WrongSize}: " << message_ << "; " << what();
	}
};
	
class IsNotSquare : public WrongDimension
{
private:
	int index_row_; int index_column_;
public:
	IsNotSquare(const char *message, const int &index_row, const int &index_column) : WrongDimension(message)
	{
		index_row_ = index_row; index_column_ = index_column;
	}

	~IsNotSquare() {}

	void print()
	{
		std::cout << '\n' << "{IsNotSquare}: " << message_;
	}
};



template<class Type> class Matrix
{
public:

	// default constructor --> { rows_ = 2; columns_ = 2; each element = 1; } 
	Matrix<Type>(const int &rows = 2, const int &columns = 2)
	{

		rows_ = rows; columns_ = columns;

		matrix_ = new Type *[rows_ + 1]; matrix_[0] = nullptr;
		for (int itt = 1; itt <= rows_; itt++)
		{
			matrix_[itt] = new Type[columns_ + 1];
		}

		/*Prefer Single allocation.
		You are allocating an array of pointers.
		Then for each pointer allocating an array of int.
		Rather than do this. Calculate the total area of the matrix N*M just
		do one allocation for all the elements.
		When somebody accesses [a][b], ou need to multiply a by the size
		of the row then add b to get the correct location of the element.*/

		// matrix[4][3] // => Gets matrix[4] (a pointer)
		//	 // => a pointer[3]   (second memory access)
		// index = (4 * rowSize) + 3;
		// return data(index);
	}

	// constructor_copy : create a copy of existing `matrix`;
	Matrix<Type>(const Matrix<Type> &matrix)
	{

		rows_ = matrix.rows_; columns_ = matrix.columns_;

		matrix_ = new Type* [rows_ + 1];
		for (int itt = 1; itt <= rows_; itt++)
		{
			matrix_[itt] = new Type[columns_ + 1];
			for (int utt = 1; utt <= columns_; utt++)
			{
				matrix_[itt][utt] = matrix.matrix_[itt][utt];
			}
		}

	}

	~Matrix<Type>()
	{

		if (matrix_ != nullptr)
		{
			for (int itt = 1; itt <= rows_; itt++) { delete[] matrix_[itt]; matrix_[itt] = nullptr; } 	             
			
			delete[] matrix_; matrix_ = nullptr;
			rows_ = columns_ = 0;
		}

	}

	// operator = : A = B
	Matrix<Type>& operator= (const Matrix &matrix) // NOT CONSTANT
	{

		if (rows_ != matrix.rows_)
		{
			// throw WrongSize("operator= : Unequal size of matrices : { rows_ }", rows_, columns_ , matrix.rows_, matrix.columns_);

			// delete old matrix
			for (int itt = 1; itt <= rows_; itt++)
			{
				delete[] matrix_[itt];
				matrix_[itt] = nullptr;
			}
			delete matrix_;
			matrix_ = nullptr;

			// create matrix_ == matrix.matrix_
			matrix_ = new Type* [rows_];
			for (int itt = 1; itt <= rows_; itt++)
			{
				matrix_[itt] = new Type[columns_];
			}
		}
		else if (columns_ != matrix.columns_)
		{
			// throw WrongSize("operator= : Unequal size of matrices : { columns_ }", rows_, columns_, matrix.rows_, matrix.columns_);

			for (int itt = 0; itt < rows_; itt++)
			{
				delete[] matrix_[itt];
				matrix_[itt] = nullptr;

				matrix_[itt] = new Type[columns_];
			}
		}

		for (int itt = 1; itt <= rows_; itt++)
		{
			for (int utt = 1; utt <= columns_; utt++)
			{
				matrix_[itt][utt] = matrix.matrix_[itt][utt];
			}
		}


		return *this;
	}

	// oparatror[][]
	Type* operator[] (int row)
	{
		if (row <= rows_ && row > 0) { return matrix_[row]; }
		else { throw IndexOutOfBounds("operator[]: Index out of bounds", rows_, columns_); }
		
	}

	/*class Proxy
	{
	protected:
		int* Proxy_array;
	public:
		Proxy(int* _array) : Proxy_array(Proxy_array) { }

		int operator[](int index) { return Proxy_array[index]; }
	};

	Proxy operator[](int index) {
		return Proxy(matrix_[index]);
	}*/

	// transposing 
	Matrix<Type> operator! () const
	{

		 if (rows_ != columns_) { throw IsNotSquare("operator!: The matrix is not square: { rows_ != columns_ }", rows_, columns_); }

		Matrix<Type> result(rows_, columns_);

		for (int itt = 1; itt <= rows_; itt++)
		{
			for (int utt = 1; utt <= columns_; utt++)
			{
				result.matrix_[itt][utt] = matrix_[utt][itt];
			}
		}


		return result;
	}

	// Matrix::matrix1 += Matrix::mвtrix2
	Matrix<Type> operator+= (const Matrix &matrix) 
	{

		if (rows_ != matrix.rows_)
		{
			throw WrongSize("operator= : Unequal size of matrices : { rows_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}
		else if (columns_ != matrix.columns_)
		{
			throw WrongSize("operator= : Unequal size of matrices : { columns_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}

		for (int itt = 1; itt <= rows_; itt++)
		{
			for (int utt = 1; utt <= columns_; utt++)
			{
				matrix_[itt][utt] += matrix.matrix_[itt][utt];
			}
		}
		

		return *this;
	}

	// Matrix::matrix1 + Matrix::matrix2 = Matrix::matrix3; return Matrix::matrix3
	Matrix<Type> operator+ (const Matrix &matrix) const
	{
		// почему я должен здесь создавать матрицу `res`
		// возвращать именно её, не изменяя первую матрицу?
		
		Matrix result(*this);

		return (result += matrix);
	}

	// Matrix += Type
	Matrix<Type> operator+= (const Type &value)
	{

		for (int itt = 1; itt <= rows_; itt++)
		{
			for (int utt = 1; utt <= columns_; utt++)
			{
				matrix_[itt][utt] += value;
			}
		}


		return *this;
	}

	// Matrix + Type 
	Matrix<Type> operator+ (const Type &value) const
	{
		Matrix result(*this);


		return (result += value);
	}

	// Matrix -= Type
	Matrix<Type> operator-= (const Type &value)
	{
		return (*this += (-value));
	}

	// Matrix - Type
	Matrix<Type> operator- (const Type &value) const
	{
		return (*this -= value);
	}

	// Matrix --> -Matrix
	Matrix<Type> operator- () const
	{
		Matrix result(*this);

		for (int itt = 1; itt <= rows_; itt++)
		{
			for (int jtt = 1; jtt <= columns_; jtt++)
			{
				result.matrix_[itt][jtt] = -matrix_[itt][jtt];
			}
		}


		return result;
	}

	// Matrix -= Matrix
	Matrix<Type> operator-= (const Matrix &matrix)
	{
		return (*this += (-matrix));
	}

	// Matrix - Matrix 
	Matrix<Type> operator- (const Matrix &matrix) const
	{
		return (*this + (-matrix));
	}

	int GetMatrixColumns() { return columns_; } const 
	int GetMatrixRows() { return rows_; } const
	void SetValue(const int &row, const int &column, int value)
	{
		if ( (row <= 0 || row > rows_) || (column <= 0 || column > columns_ ) )
		{
			throw IndexOutOfBounds("method: \'SetValue(const int &row, const int &column, int value)\' : Index out of bounds", row, column);
		}
		else { matrix_[row][column] = value; }
	}

	void output_() const
	{
		std::cout  << '\n'; 

		for (int itt = 1; itt <= rows_; itt++)
		{
			if (itt == 1) { std::cout  << "T"; }
			else if (itt == rows_) { std::cout  << "L"; }
			else { std::cout  << "|"; }
			
			for (int jtt = 1; jtt <= columns_; jtt++)
			{
				// std::cout  << " " << std::manipulator_custom << matrix_[itt][jtt];
				std::cout << " " << matrix_[itt][jtt];
			}
		
			if (itt == 1) { std::cout  << " T"; }
			else if (itt == rows_) { std::cout  << " J"; }
			else { std::cout  << " |"; }

			std::cout  << '\n';
		}
		
		std::cout  << '\n';
	}

	// find amount of symbols in num from method Matrix<Type>::dog
	int human(const int &value) const
	{
		int value_copy = value;
		int length = 0;
		while (value_copy > 0)
		{
			value_copy /= 10; length++;
		}


		return length;
	}

	// find max value in row
	int dog(const int &column) const
	{
		int result = 0;
		for (int itt = 1; itt <= rows_; itt++)
		{
			result = ( matrix_[itt][column] > result ) ? matrix_[itt][column] : result;
		}


		return ( human(result) );
	}
	
	void print_() const	
	{
		std::cout << '\n';

		for (int itt = 1; itt <= rows_; itt++)
		{
			if (itt == 1) { std::cout << "T"; }
			else if (itt == rows_) { std::cout << "L"; }
			else { std::cout << "|"; }

			for (int jtt = 1; jtt <= columns_; jtt++)
			{
				std::cout << " ";
				int length_max = dog(jtt);
				int length = human(matrix_[itt][jtt]); length = ((length_max - length) % 2 == 0) ? (length_max - length) / 2 : (length_max - length ) / 2;
				for (int step = 0; step < length; step++)
				{
					std::cout << " ";
				}
				std::cout  << matrix_[itt][jtt];
				for (int step = 0; step < length; step++)
				{
					std::cout << " ";
				}
				std::cout << " ";
			}

			if (itt == 1) { std::cout << " T"; }
			else if (itt == rows_) { std::cout << " J"; }
			else { std::cout << " |"; }

			std::cout << '\n';
		}

		std::cout << '\n';
	}


	template <class Type> friend std::ostream& operator<< (std::ostream &output, const Matrix<Type> &matrix);
	template <class Type> friend std::istream& operator>> (std::istream &input, Matrix<Type> &matrix);
	


protected:
	Type** matrix_;
	int rows_;
	int columns_;
};

template<class Type> std::ostream& operator<< (std::ostream &output, const Matrix<Type> &matrix)
{
	if (typeid(output).name() == typeid(std::ofstream).name())
	{
		output << matrix.rows_ << " " << matrix.columns_ << '\n';

		for (int utt = 1; utt <= matrix.rows_; utt++)
		{
			for (int vtt = 1; vtt <= matrix.columns_; vtt++)
			{
				output << matrix.matrix_[utt][vtt] << " ";
			}
			output << '\n';
		}
	}
	else
	{
		output << '\n';

		for (int itt = 1; itt <= matrix.rows_; itt++)
		{
			if (itt == 1) { output << "T"; }
			else if (itt == matrix.rows_) { output << "L"; }
			else { output << "|"; }

			for (int jtt = 1; jtt <= matrix.columns_; jtt++)
			{
				output << " ";
				int length_max = matrix.dog(jtt);
				int length = matrix.human(matrix.matrix_[itt][jtt]); length = ((length_max - length) % 2 == 0) ? (length_max - length) / 2 : (length_max - length) / 2;
				for (int step = 0; step < length; step++)
				{
					output << " ";
				}
				output << matrix.matrix_[itt][jtt];
				for (int step = 0; step < length; step++)
				{
					output << " ";
				}
				output << " ";
			}

			if (itt == 1) { output << " T"; }
			else if (itt == matrix.rows_) { output << " J"; }
			else { output << " |"; }

			output << '\n';
		}

	}
	
	output << '\n';
	return output;
}

template<class Type> std::istream& operator>> (std::istream &input, Matrix<Type> &matrix)
{
	int rows, cols; input >> rows >> cols;

	if (matrix.rows_ != rows || matrix.columns_ != cols)
	{
		for (int itt = 1; itt <= matrix.rows_; itt++)
		{
			delete[] matrix.matrix_[itt];
			matrix.matrix_[itt] = nullptr;
		}
		delete matrix.matrix_;
		matrix.matrix_ = nullptr;

		// create matrix_ == matrix.matrix_
		matrix.matrix_ = new Type* [rows + 1];
		for (int itt = 1; itt <= rows; itt++)
		{
			matrix.matrix_[itt] = new Type[cols + 1];
		}

		matrix.rows_ = rows; matrix.columns_ = cols;
	}

	for (int itt = 1; itt <= rows; itt++)
	{
		for (int utt = 1; utt <= cols; utt++)
		{
			input >> matrix.matrix_[itt][utt];
		}
	}


	return input;
}

std::ostream& manipulator_custom(std::ostream& output)
{
	output.fill(' ');
	output.width(6);
	// output.left();


	return output;
}



template<class Type> class subMatrix : public Matrix<Type>
{
public:

	// default_constructor
	subMatrix<Type> (const int &rows = 2, const int &columns = 2) : Matrix<Type>(rows, columns) {}

	// constructor_copy: subMatrix::sub_matrix --> subMatrix::(copy of matrix)
	subMatrix<Type> (const subMatrix<Type> &sub_matrix) : Matrix<Type> (sub_matrix) {}

	// constructor_copy: Matrix::matrix --> subMatrix::(copy of matrix) 
	subMatrix<Type> (const Matrix<Type> &matrix) : Matrix<Type>(matrix) {}

	// destructor
	~subMatrix<Type>() {};
	
	// filling matrix of random values NOT CONST // ONLY double type DK HOW TO GENERALIZY
	subMatrix<Type> RandFill()
	{

		for (int itt = 1; itt <= Matrix<Type>::rows_; itt++)
		{
			for (int jtt = 1; jtt <= Matrix<Type>::columns_; jtt++)
			{
				Matrix<Type>::matrix_[itt][jtt] = std::rand();
			}
		}
		

		return (*this);
	}
	
	subMatrix<Type> Smoothing() const
	{
		subMatrix<Type> result(*this);

		for (int itt = 1; itt <= result.rows_; itt++)
		{
			for (int jtt = 1; jtt <= result.columns_; jtt++)
			{
				if (jtt == 1)
				{
					result.matrix_[itt][jtt] = (Matrix<Type>::matrix_[itt][jtt] + Matrix<Type>::matrix_[itt][jtt + 1] ) / 2;
				}
				else if (jtt == result.Matrix<Type>::columns_)
				{
					result.matrix_[itt][jtt] = (Matrix<Type>::matrix_[itt][jtt] + Matrix<Type>::matrix_[itt][jtt - 1]) / 2;
				}
				else 
				{
					result.matrix_[itt][jtt] = (Matrix<Type>::matrix_[itt][jtt - 1] + Matrix<Type>::matrix_[itt][jtt + 1]) / 2;
				}
			}
		}


		return result;
	}
	
	
};



int main()
{

	// Задание 5.1: Проверка общей работоспособности системы.
	//////////////////////////////////////////////////////////////////////////////
	Matrix<double> test(5, 5);
	int rows = test.GetMatrixRows();
	int columns = test.GetMatrixColumns();
	for (int itt = 1; itt <= rows; itt++)
	{
		for (int jtt = 1; jtt <= columns; jtt++)
		{
			test.SetValue(itt, jtt, std::rand());
		}
	}
	watch(test);
	test.print_();

	Matrix<double> matrix_1(2, 2);
	for (int itt = 1; itt <= matrix_1.GetMatrixRows(); itt++)
	{
		for (int jtt = 1; jtt <= matrix_1.GetMatrixColumns(); jtt++)
		{
			matrix_1.SetValue(itt, jtt, (itt + jtt));
		}
	}
	Matrix<double> matrix_2(2, 2);
	for (int itt = 1; itt <= matrix_1.GetMatrixRows(); itt++)
	{
		for (int jtt = 1; jtt <= matrix_1.GetMatrixColumns(); jtt++)
		{
			matrix_2.SetValue(itt, jtt, (itt + jtt + 4));
		}
	}


	watch(matrix_1);  matrix_1.print_();
	watch(matrix_2);  matrix_2.print_();

	matrix_1 += matrix_2; watch(matrix_1);  matrix_1.print_();
	matrix_2 += 99; watch(matrix_2);  matrix_2.print_();

	matrix_2 -= matrix_1; watch(matrix_2);  matrix_2.print_();

	(-matrix_1).print_();


	subMatrix<double> sub_test(test);
	sub_test.RandFill();
	watch(sub_test);
	sub_test.print_();

	sub_test.SetValue(2, 2, 99999);
	watch(sub_test);
	sub_test.print_();

	subMatrix<double> sub_test_smothed = sub_test.Smoothing();
	watch(sub_test_smothed);
	sub_test_smothed.print_();
	//////////////////////////////////////////////////////////////////////////////

	// Задание 5.2: Поимка и обработка исключений.
	//////////////////////////////////////////////////////////////////////////////
	Matrix<double> matrix(4, 4);
	try
	{
		// Обращение к элементам матрицы по неправильным индексам. Пусть матрица Matrix::matrix
		// имеет размеры 4x4. Обратимся к элементу matrix[5][5].
		std::cout  << matrix[5][5];

	}
	catch (IndexOutOfBounds index_incorrect)
	{
		index_incorrect.print();

		// Обраотем исключение. Возможно пользователь хотел обратиться к крайнему элементу матрицы, но перепутал 
		// размерность, спросим его об этом.
		std::cout  << '\n' << "Perhaps you meant: matrix[" << matrix.GetMatrixRows() << "][" << matrix.GetMatrixColumns() << "]"
			<< "(y/N)?" << '\n';
		std::string user_answer; std::cin >> user_answer;
		if (user_answer == "y") { std::cout  << matrix[matrix.GetMatrixRows()][matrix.GetMatrixColumns()] << '\n'; }
		else { std::cout  << "Check the correctness of the indexes. Please, try again" << '\n'; }
	}

	subMatrix<double> sub_matrix(2, 3); sub_matrix.RandFill(); sub_matrix.print_();
	try
	{
		// Попробуем транспонировать неквадратную матрицу.
		sub_matrix = !(sub_matrix);
	}
	catch (IsNotSquare dimension_incorrect)
	{
		dimension_incorrect.print();
		std::cout  << " Check the correctness of the matrix dimensions(matrix is not square). Please, try again" << '\n';
	}

	try
	{
		// Поймаем и обработаем родительский класс ошибок. Например, сложив матрицы разных размерностей.
		matrix += sub_matrix;
	}
	catch (Exception exception)
	{
		exception.print();
		std::cout  << " Check the correctness of the matrices dimensions. Please, try again" << '\n';
	}
	catch (...)
	{
		std::cout  << "Ooopsy-doopsy, something was wrong; the developer should be punished. Do you wanna message about it my boss (y/N)?" << '\n';
		std::string user_answer;
		std::cin >> user_answer; 
		if (user_answer == "y" || user_answer == "Y") {
			std::cout << "Speaking out against the developers was a bad idea. You're going to pay for this, AHAHAHAHAHA!" << '\n'; exit(EXIT_FAILURE); }
		else { std::cout  << "thanks for your silent!" << '\n'; }
	}

	//////////////////////////////////////////////////////////////////////////////

	// Задание 5.3: Чтение и запись в файл.
	//////////////////////////////////////////////////////////////////////////////
	subMatrix<double> cc1(9,1), cc2(8,5);
	cc1.RandFill(); cc2.RandFill();

	std::ofstream file_out; file_out.open("practice5[5.3].txt", std::ios::out);
	if (file_out)
	{
		file_out << cc1 << cc2;
		file_out.close();
	}

	std::ifstream file_in("practice5[5.3].txt", std::ios::in);
	if (file_in)
	{
		try
		{
			subMatrix<double> matrix_in1(2,8), matrix_in2(15,10);
			matrix_in1.RandFill(); matrix_in2.RandFill();

			file_in >> matrix_in1 >> matrix_in2;
			file_in.close();
			std::cout << '\n' << matrix_in1 << '\n' << matrix_in2;
		}
		catch (...)
		{
			std::cout << '\n' << "Exception: failed to read file";
		}
	}
	

	//////////////////////////////////////////////////////////////////////////////
	return 0;
}

