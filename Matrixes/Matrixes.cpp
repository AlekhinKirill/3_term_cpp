#include<iostream>;
using namespace std;

class Matrix
{
public:
	int height;
	int width;
	int** data;
	Matrix(int height, int width) : height(height), width(width)
	{
		int i, j;
		this->data = new int* [height];
		for (i = 0; i < height; i++)
		{
			this->data[i] = new int[width];
			for (j = 0; j < width; j++)
				this->data[i][j] = 0;
		}
	}

	Matrix(int size) : Matrix(size, size) {}

	Matrix(int height, int width, int** data) : height(height), width(width), data(data) {}

	Matrix(int size, int** data) : Matrix(size, size, data) {}

	Matrix() :Matrix(0, nullptr) {};
	/*
	~Matrix()
	{
		int i;
		for (i = 0; i < this->height; i++)
			delete[] this->data[i];
		delete[] data;
	};
	*/
	Matrix transponation()
	{
		int i, j;
		Matrix new_matrix(this->width, this->height);
		for (i = 0; i < this->width; i++)
			for (j = 0; j < this->height; j++)
				new_matrix.data[i][j] = this->data[j][i];
		return new_matrix;
	}
};

ostream& operator<<(ostream& out, Matrix& matrix)
{
	int i, j;
	for (i = 0; i < matrix.height; i++)
	{
		for (j = 0; j < matrix.width; j++)
			out << matrix.data[i][j] << " ";
		out << endl;
	}
	return out;
}

Matrix operator>>(istream& in, Matrix& matrix)
{
	int i, j;
	cout << "Please, enter matrix's dimensions (height and width) and then the matrix itself";
	in >> matrix.height;
	in >> matrix.width;
	for (i = 0; i < matrix.height; i++)
	{
		for (j = 0; j < matrix.width; j++)
			in >> matrix.data[i][j];
	}
	Matrix new_matrix(matrix.height, matrix.width, matrix.data);
	return new_matrix;
}

Matrix operator+(Matrix first_matrix, Matrix second_matrix)
{
	if ((first_matrix.height == second_matrix.height) && (first_matrix.width == second_matrix.width))
	{
		int i, j;
		Matrix new_matrix(first_matrix.height, first_matrix.width);
		for (i = 0; i < first_matrix.height; i++)
			for (j = 0; j < first_matrix.width; j++)
				new_matrix.data[i][j] = first_matrix.data[i][j] + second_matrix.data[i][j];
		return new_matrix;
	}
	else
		cout << "The addition is impossible" << endl;
}


Matrix operator*(int scalar, Matrix matrix)
{
	Matrix new_matrix(matrix.height, matrix.width);
	int i, j;
	for (i = 0; i < new_matrix.height; i++)
		for (j = 0; j < new_matrix.width; j++)
			new_matrix.data[i][j] = scalar*matrix.data[i][j];
	return new_matrix;
}

Matrix operator*(Matrix first_matrix, Matrix second_matrix)
{
	if (first_matrix.width == second_matrix.height)
	{
		int i, j, k;
		Matrix new_matrix(first_matrix.height, second_matrix.width);
		for (i = 0; i < first_matrix.height; i++)
			for (j = 0; j < first_matrix.width; j++)
				for (k = 0; k < first_matrix.width; k++)
					new_matrix.data[i][j] += first_matrix.data[i][k]*second_matrix.data[k][j];
		return new_matrix;
	}
	else
		cout << "The multiplication is impossible" << endl;
}

Matrix operator-(Matrix first_matrix, Matrix second_matrix)
{
	if ((first_matrix.height == second_matrix.height) && (first_matrix.width == second_matrix.width))
	{
		Matrix new_matrix = first_matrix + (-1) * second_matrix;
		return new_matrix;
	}
	else
		cout << "The subtaraction is impossible" << endl;
}

class Vector : public Matrix
{
public:
	Vector(int size) : Matrix(1, size) {};
	Vector(int size, int* array)
	{
		int** new_data = new int* [1];
		new_data[0] = array;
		height = 1;
		width = size;
		data = new_data;
	}
};

int scalar_product(Vector first_vector, Vector second_vector)
{
	return (first_vector * (second_vector.transponation())).data[0][0];
}

int main()
{
	int i;
	// Matrix A
	int height = 4;
	int width = 4;
	int** data_A = new int* [height];
	for (i = 0; i < height; i++)
		data_A[i] = new int[width];
	data_A[0][0] = 3; data_A[0][1] = -2; data_A[0][2] = 5; data_A[0][3] = 1;
	data_A[1][0] = 1; data_A[1][1] = 7; data_A[1][2] = -1; data_A[1][3] = -4;
	data_A[2][0] = 6; data_A[2][1] = -8; data_A[2][2] = 10; data_A[2][3] = 0;
	data_A[3][0] = 2; data_A[3][1] = 3; data_A[3][2] = -9; data_A[3][3] = 5;
	// Matrix B
	int** data_B = new int* [height];
	for (i = 0; i < height; i++)
		data_B[i] = new int[width];
	data_B[0][0] = 5; data_B[0][1] = 1; data_B[0][2] = 4; data_B[0][3] = 8;
	data_B[1][0] = 9; data_B[1][1] = -3; data_B[1][2] = 7; data_B[1][3] = 8;
	data_B[2][0] = 0; data_B[2][1] = 3; data_B[2][2] = 1; data_B[2][3] = 2;
	data_B[3][0] = -7; data_B[3][1] = 6; data_B[3][2] = 0; data_B[3][3] = 10;
	Matrix A(4, data_A);
	Matrix B(4, data_B);
	Matrix O(5, 6);
	cout << A;
	cout << endl;
	cout << B;
	cout << endl;
	Matrix C = A + B;
	Matrix D = A * B;
	Matrix F = 2 * C;
	Matrix G = A - B;
	Matrix H = G.transponation();
	cout << C;
	cout << endl;
	cout << F;
	cout << endl;
	cout << D;
	cout << endl;
	cout << G;
	cout << endl;
	cout << H;
	cout << endl;
	int* array_a = new int[3];
	array_a[0] = 2; array_a[1] = 3; array_a[2] = -5;
	Vector a(3, array_a);
	int* array_b = new int[3];
	array_b[0] = 1; array_b[1] = -7; array_b[2] = 2;
	Vector b(3, array_b);
	cout << a;
	cout << endl;
	cout << b;
	cout << endl;
	cout << scalar_product(a, b);
}