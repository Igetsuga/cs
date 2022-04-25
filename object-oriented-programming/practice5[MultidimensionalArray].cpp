// Сиразетдинов Рустем КМБО-01-21 Вариант 24

#include <random>

#include <iostream>
using std::cin;
using std::cout;

#define watch(variable) cout << "Matix: " << (#variable)

// есть ли разница в скорости при выделении памяти? Т.е. быстрее выделится меньше памяти? 
// Как много памяти можно выделять за 1 раз.

// когда нужно возвращать ссылку, а когда копию объекта?
class Matrix
{
protected:
	double **matrix_;
	int rows_;
	int columns_;
public:

	// default constructor --> { rows_ = 2; columns_ = 2; each element = 1; } 
	Matrix(const int &rows = 2, const int &columns = 2)
	{

		rows_ = rows; columns_ = columns;

		matrix_ = new double *[rows_];
		for (int itt = 0; itt < rows_; itt++)
		{
			matrix_[itt] = new double[columns_];
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
	Matrix(const Matrix &matrix)
	{

		rows_ = matrix.rows_; columns_ = matrix.columns_;

		matrix_ = new double* [rows_];
		for (int itt = 0; itt < rows_; itt++)
		{
			matrix_[itt] = new double[columns_];
			for (int utt = 0; utt < columns_; utt++)
			{
				matrix_[itt][utt] = matrix.matrix_[itt][utt];
			}
		}

	}

	~Matrix()
	{

		if (matrix_ != nullptr)
		{
			for (int itt = 0; itt < rows_; itt++) { delete[] matrix_[itt]; } // почему здесь не нужно писать
																			  // matrix[itt] = nullptr;	             
			delete[] matrix_;

			matrix_ = nullptr;
		}

	}

	// operator = : A = B
	Matrix& operator= (const Matrix &matrix) // NOT CONSTANT
	{

		if (rows_ != matrix.rows_)
		{
			// throw UnequalSize("operator= : Unequal size of matrices : { rows_ }", rows_, columns_ , matrix.rows_, matrix.columns_);

			// delete old matrix
			for (int itt = 0; itt < rows_; itt++)
			{
				delete[] matrix_[itt];
				matrix_[itt] = nullptr;
			}
			delete matrix_;
			matrix_ = nullptr;

			// create matrix_ == matrix.matrix_
			matrix_ = new double* [rows_];
			for (int itt = 0; itt < rows_; itt++)
			{
				matrix_[itt] = new double[columns_];
			}
		}
		else if (columns_ != matrix.columns_)
		{
			// throw UnequalSize("operator= : Unequal size of matrices : { columns_ }", rows_, columns_, matrix.rows_, matrix.columns_);

			for (int itt; itt < rows_; itt++)
			{
				delete[] matrix_[itt];
				matrix_[itt] = nullptr;

				matrix_[itt] = new double[columns_];
			}
		}

		for (int itt, utt = 0; itt < rows_, utt < columns_; itt++, utt++)
		{
			matrix_[itt][utt] = matrix.matrix_[itt][utt];
		}


		return *this;
	}

	// oparatror[][]
	double* operator[] (int row)
	{
		return matrix_[row];
	}


	// transposing 
	Matrix operator! () const
	{

		// if (rows_ != columns_) { throw TheMatrixIsNotSquare("operator! : The matrix is not square : { rows_ != columns_ }", rows_, columns_); }

		Matrix result(rows_, columns_);

		for (int itt = 0; itt < rows_; itt++)
		{
			for (int utt = 0; utt < columns_; utt++)
			{
				result.matrix_[itt][utt] = matrix_[utt][itt];
			}
		}


		return result;
	}

	// matrix_1 += matrix_2
	Matrix operator+= (const Matrix &matrix) const
	{

		/*if (rows_ != matrix.rows_)
		{
			throw UnequalSize("operator= : Unequal size of matrices : { rows_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}
		else if (columns_ != matrix.columns_)
		{
			throw UnequalSize("operator= : Unequal size of matrices : { columns_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}*/

		for (int itt, utt = 0; itt < rows_, utt < columns_; itt++, utt++)
		{
			matrix_[itt][utt] += matrix.matrix_[itt][utt];
		}

		return *this;
	}

	// matrix_1 + matrix_2 = matrix_3; return matrix_3
	Matrix operator+ (const Matrix &matrix) const
	{
		// почему я должен здесь создавать матрицу `res`
		// возвращать именно её, не изменяя первую матрицу?
		/*if (rows_ != matrix.rows_)
		{
			throw UnequalSize("operator= : Unequal size of matrices : { rows_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}
		else if (columns_ != matrix.columns_)
		{
			throw UnequalSize("operator= : Unequal size of matrices : { columns_ }", rows_, columns_, matrix.rows_, matrix.columns_);
		}*/

		Matrix result(*this);

		return (result += matrix);
	}

	// matrix += double
	Matrix operator+= (const double &value)
	{

		for (int itt, utt = 0; itt < rows_, utt < columns_; itt++, utt++)
		{
			matrix_[itt][utt] += matrix_[itt][utt];
		}


		return *this;
	}

	// matrix + double 
	Matrix operator+ (const double &value) const
	{
		Matrix result(*this);


		return (result += value);
	}

	Matrix operator-= (const double &value) const
	{
		return (*this += (-value));
	}

	Matrix operator- (const double &value) const
	{
		return (*this -= value);
	}

	Matrix& operator- () const
	{
		Matrix result(*this);

		for (int itt = 0; itt < rows_; itt++)
		{
			for (int jtt = 0; jtt < columns_; jtt++)
			{
				result.matrix_[itt][jtt] = matrix_[itt][jtt];
			}
		}


		return result;
	}

	Matrix operator-= (const Matrix &matrix)
	{
		return (*this += (-matrix));
	}

	Matrix operator- (const Matrix &matrix) const
	{
		return (*this + (-matrix));
	}

	int GetMatrixColumns() { return columns_; }
	int GetMatrixRows() { return rows_; }

	void print_()
	{
		cout << '\n'; 

		for (int itt = 0; itt < rows_; itt++)
		{
			if (!itt) { cout << "T"; }
			else if (itt == rows_ - 1) { cout << "L"; }
			else { cout << "|"; }
			
			for (int jtt = 0; jtt < columns_; jtt++)
			{
				cout << " " << matrix_[itt][jtt];
			}
		
			if (!itt) { cout << " T"; }
			else if (itt == rows_ - 1) { cout << " J"; }
			else { cout << " |"; }

			cout << '\n';
		}
		
		cout << '\n';
	}

	
	
};

class subMatrix : public Matrix
{
public:

	// default_constructor
	subMatrix(const int &rows = 2, const int &columns = 2) : Matrix(rows, columns) {}

	// constructor_copy: subMatrix::sub_matrix --> subMatrix::(copy of matrix)
	subMatrix(const subMatrix &sub_matrix) : Matrix(sub_matrix) {}

	// constructor_copy: Matrix::matrix --> subMatrix::(copy of matrix) 
	subMatrix(const Matrix &matrix) : Matrix(matrix) {}
	
	// filling matrix of random values NOT CONST
	Matrix RandFill()  // если я здесь уберу 
					   // наследование от родительского 
					   // конструктора, тогда какой конструтор
					   // будет вызываться?
	{

		for (int itt = 0; itt < rows_; itt++)
		{
			for (int jtt = 0; jtt < columns_; jtt++)
			{
				matrix_[itt][jtt] = std::rand();
			}
		}
		

		return (*this);
	}
	
	Matrix Smoothing(const subMatrix &sub_matrix) const
	{
		for (int itt = 0; itt < rows_; itt++)
		{
			for (int jtt = 0; jtt < columns_; jtt++)
			{
				if (jtt == 0)
				{
					matrix_[itt][jtt] = ( matrix_[itt][jtt] + matrix_[itt][jtt + 1] ) / 2;
				}
				else if (jtt == columns_ - 1)
				{
					matrix_[itt][jtt] = (matrix_[itt][jtt] + matrix_[itt][jtt - 1]) / 2;
				}
				else 
				{
					matrix_[itt][jtt] = (matrix_[itt][jtt - 1] + matrix_[itt][jtt + 1]) / 2;
				}
			}
		}
	}
	


	
};


int main()
{





	Matrix test(5, 5);
	int rows = test.GetMatrixRows();
	int columns = test.GetMatrixColumns();
	for (int itt = 0; itt < rows; itt++)
	{
		for (int jtt = 0; jtt < columns; jtt++)
		{
			test[itt][jtt] = std::rand();
		}
	}

	watch(test);
	test.print_();

	subMatrix sub_test(test);
	sub_test.RandFill();
	watch(sub_test);
	sub_test.print_();

	sub_test[2][2] = 99999;
	watch(sub_test);
	sub_test.print_();


	return 0;
}