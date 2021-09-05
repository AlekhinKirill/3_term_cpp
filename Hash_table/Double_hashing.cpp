#include <iostream>
#include <string>
using namespace std;

class Cell
{
public:
	string str;
	int indicator; // 0 - ячейка удалена; 1 - ячейка не удалена
	Cell()
	{
		str = "empty";
		indicator = 1;
	}
};

class Array
{
public:
	int length;
	int memory;
	Cell* data;
	Array(int size, int lenght)
	{
		int i;
		length = 0;
		memory = size;
		Cell* new_array = new Cell[memory];
		data = new_array;
	}
};

int hash_function(int prime, string str, int table_len)
{
	int i, hash;
	hash = 0;
	for (i = 0; i < size(str); i++)
	{
		hash = (prime * hash + str[i]) % table_len;
	}
	if (hash % 2 == 0)
		hash++;
	return hash;
}


class Hash_table
{
public:
	Array array{ 8, 0 };
	Hash_table() // конструктор по умолчанию (пустая таблица)
	{
		Array new_array{ 8, 0 };
		array = new_array;
	}
	Array add(string str)
	{
		if (array.memory - 1 == array.length)
		{
			int i;
			Array new_array{ array.memory * 2 , array.memory };
			Array privious_array = array;
			array = new_array;
			for (i = 0; i < privious_array.memory; i++)
				if ((privious_array.data[i].indicator == 1) && (privious_array.data[i].str != "empty"))
					add(privious_array.data[i].str);
			add(str);
		}
		else
		{
			int step, k;
			k = 0;
			step = hash_function(23, str, array.memory);
			if (step == 0)
				step++;
			while ((array.data[(hash_function(41, str, array.memory) + k * step) % array.memory].str != "empty") && (array.data[(hash_function(41, str, array.memory) + k * step) % array.memory].indicator == 1))
				k++;
			array.data[(hash_function(41, str, array.memory) + k * step) % array.memory].str = str;
			array.length++;
		}
		return array;
	}

	void print()
	{
		int i;
		for (i = 0; i < array.memory; i++)
		{
			if (array.data[i].indicator == 1)
				cout << array.data[i].str << endl;
			else
				cout << "empty" << endl;
		}
	}

	int index(string str)
	{
		int hash1, hash2, k;
		hash1 = hash_function(41, str, array.memory);
		hash2 = hash_function(23, str, array.memory);
		k = 0;
		while ((array.data[(hash1 + k * hash2) % array.memory].str != str) && (array.data[(hash1 + k * hash2) % array.memory].str != "empty"))
			k++;
		if (array.data[(hash1 + k * hash2) % array.memory].str == str)
		{
			if (array.data[(hash1 + k * hash2) % array.memory].indicator == 1)
				return (hash1 + k * hash2) % array.memory;
		}
		else
			return -1;
	}

	void find(string str)
	{
		if (index(str) == -1)
			cout << "There is no " << "" << str << "" << " in the table" << endl;
		else
			cout << """" << str << "" << " exists in the table and its number is " << index(str) + 1 << endl;
	}
	Array remove(string str)
	{
		if (index(str) == -1)
			cout << "There is no " << "" << str << "" << " in the table. Deleting is impossible" << endl;
		else
		{
			array.data[index(str)].indicator = 0;
			array.length--;
		}
		return array;
	}
};


int main()
{
	Hash_table table{};
	table.add("Matematics");
	table.add("Physics");
	table.add("Informatics");
	table.add("Linal");
	table.add("Astronomy");
	table.add("Matan");
	table.add("Mechanics");
	table.add("Termodynamics");
	table.add("Geometry");
	table.remove("Termodynamics");
	table.print();
	cout << endl;
	table.find("Astronomy");
	table.find("Potato");
}