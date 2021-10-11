#include<iostream>
using namespace std;


template <typename T>
class Grid
{
private:
	T** memory;
	size_t x_size, y_size;

public:
	Grid() = delete;
	Grid(size_t size_y, size_t size_x) : x_size(size_x), y_size(size_y)
	{
		this->memory = new T * [size_y];
		for (size_t i = 0; i < size_y; i++)
			this->memory[i] = new T[size_x];
	};
	~Grid() 
	{
		cout << "Destruction" << endl;
		for (size_t i = 0; i < this->y_size; i++)
			delete[] memory[i];
		delete[] memory;
	};

	size_t get_xsize() const
	{
		return this->x_size;
	}

	size_t get_ysize() const
	{
		return this->y_size;
	}

	Grid& operator=(Grid &grid)
	{
		T swap_variable;
		for (size_t i = 0; i < grid.y_size; i++)
			for (size_t j = 0; j < grid.x_size; j++)
			{
				swap_variable = grid.memory[i][j];
				this->memory[i][j] = swap_variable;
			}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Grid const& grid)
	{
		for (size_t i = 0; i < grid.get_ysize(); i++)
		{
			for (size_t j = 0; j < grid.get_xsize(); j++)
				out << grid.memory[i][j] << " ";
			out << "\n";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Grid& grid)
	{
		cout << "Enter matrix, please" << endl;
		for (size_t i = 0; i < grid.y_size; i++)
			for (size_t j = 0; j < grid.x_size; j++)
				in >> grid.memory[i][j];
		return in;
	}

	T operator()(size_t y_id, size_t x_id) const
	{
		return this->memory[y_id][x_id];
	}

	T& operator()(size_t y_id, size_t x_id)
	{
		return this->memory[y_id][x_id];
	}
};


int main()
{
	Grid<int> A{ 2, 2 };
	cin >> A;
	cout << "Result:" << endl;
	cout << A;
	Grid<int> B{ 2, 2 };
	B = A;
	int element = B.operator()(1, 0);
	cout << element << endl;
	cout << B;
}