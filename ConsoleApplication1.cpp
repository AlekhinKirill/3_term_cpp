#include <iostream>
using namespace std;

int main()
{
	int number, degree, base, factor, i, j;
	base = 1;
	degree = 0;
	cin >> number;
    while (number >= base*60)
	{
		base = base * 60;
		degree = degree + 1;
	}
	for (i = degree; i >= 0; i--)
	{
		factor = number / base;
		while (factor / 10 != 0)
		{
			cout << "<";
			factor = factor - 10;
		}
		for (j = 1; j <= factor; j++)
		{
			cout << "v";
		}
		if (i != 0)
		{
			cout << ".";
		}
		number = number % base;
		base = base / 60;
	}
}