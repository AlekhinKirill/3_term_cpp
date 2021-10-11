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

	Grid operator=(Grid grid)
	{
		cout << "Okey" << endl;
		T swap_variable;
		Grid new_grid{ grid.x_size, grid.y_size };
		for (size_t i = 0; i < grid.y_size; i++)
			for (size_t j = 0; j < grid.x_size; j++)
			{
				swap_variable = grid.memory[i][j];
				new_grid.memory[i][j] = swap_variable;
			}
		return new_grid;
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
		for (size_t i = 0; i < grid.y_size; i++)
			for (size_t j = 0; j < grid.x_size; j++)
				in >> grid.memory[i][j];
		return in;
	}
};


int main()
{
	Grid<int> A{ 2, 2 };
	cin >> A;
	cout << "Result:" << endl;
	cout << A;
	Grid<int> B = A;
	cout << B;
}