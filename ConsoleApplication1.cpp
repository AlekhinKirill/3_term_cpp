#include <iostream>
#include <vector>
using namespace std;


struct Cell
{
	int value;
	Cell* left_ptr;
	Cell* right_ptr;
	Cell* privious_ptr;
	int height_left = 0;
	int height_right = 0;
	int balance;
	bool used = false;
};

struct Tree
{
	Cell* root;
	int capacity;
	vector<Cell*> leaves;
	vector<Cell*> cells;
};

struct Queue_elements
{
	Cell* value;
	Queue_elements* next_ptr;
};

struct Queue
{
	int length;
	Queue_elements* first;
	Queue_elements* last;
};

Queue create()
{
	Queue list;
	list.length = 0;
	list.first = nullptr;
	list.last = nullptr;
	return list;
}

Queue enqueue(Queue queue, Cell* value_ptr)
{
	Queue_elements* element = new Queue_elements;
	element->value = value_ptr;
	element->next_ptr = nullptr;
	if (queue.length == 0)
	{
		queue.first = element;
		queue.last = element;
	}
	else
	{
		queue.last->next_ptr = element;
		queue.last = element;
	}
	queue.length += 1;
	return queue;
}

Queue dequeue(Queue queue)
{
	queue.first = queue.first->next_ptr;
	queue.length -= 1;
	return queue;
}

int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

void print_queue(Queue queue)
{
	Queue_elements* element_ptr;
	element_ptr = queue.first;
	cout << queue.first->value->value << " ";
	while (element_ptr->next_ptr != nullptr)
	{
		cout << element_ptr->next_ptr->value->value << " ";
		element_ptr = element_ptr->next_ptr;
	}
	cout << endl;
}

Tree create_empty(int value)
{
	Tree tree;
	Cell* root = new Cell;
	tree.capacity = 0;
	root->value = value;
	root->left_ptr = nullptr;
	root->right_ptr = nullptr;
	root->privious_ptr = nullptr;
	tree.root = root;
	return tree;
}

Queue descent(Queue queue, Cell* cell, string mod)
{
	Cell* last_knot = new Cell;
	if (mod == "print")
		cout << cell->value << "( высота левого поддерева = " << cell->height_left << " ; высота правого поддерева = " << cell->height_right << ")" << endl;
	while (cell->left_ptr != nullptr)
	{
		if (cell->right_ptr != nullptr)
			queue = enqueue(queue, cell->right_ptr);
		cell = cell->left_ptr;
		if (mod == "print")
			cout << cell->value << "( высота левого поддерева = " << cell->height_left << " ; высота правого поддерева = " << cell->height_right << ")" << endl;
	}
	if (cell->right_ptr != nullptr)
		queue = enqueue(queue, cell->right_ptr);
	queue = dequeue(queue);
	return queue;
}

void print(Tree tree)
{
	cout << endl;
	cout << "Элементы дерева" << endl;
	Queue queue = create();
	queue = enqueue(queue, tree.root);
	while (queue.length != 0)
	{
		if (queue.length != 0)
		{
			queue = descent(queue, queue.first->value, "print");
		}
	}
}

Cell* find(Cell* root, int value)
{
	if (root == nullptr)
	{
		return nullptr;
		exit;
	}
	if (value == root->value)
		return root;
	else if (value < root->value)
		return find(root->left_ptr, value);
	else
		return find(root->right_ptr, value);
}

void find_and_info(Tree tree, int key)
{
	cout << endl;
	Cell* cell;
	cell = find(tree.root, key);
	if (find(tree.root, key) == nullptr)
		cout << "Элемента " << key << " нет" << endl;
	else
	{
		cout << "Элемент " << key << " существует и про него известно следующее:" << endl;
		if (find(tree.root, key)->left_ptr != nullptr)
			cout << "Его сосед слева " << find(tree.root, key)->left_ptr->value << endl;
		else
			cout << "У него нет соседей слева " << endl;
		if (find(tree.root, key)->right_ptr != nullptr)
			cout << "Его сосед справа " << find(tree.root, key)->right_ptr->value << endl;
		else
			cout << "У него нет соседей справа " << endl;
		if (find(tree.root, key)->privious_ptr != nullptr)
			cout << "Предыдущий элемент " << find(tree.root, key)->privious_ptr->value << endl;
		else
			cout << "Это корень дерева" << endl;
		cout << "Высота левого поддерева = " << cell->height_left << endl;
		cout << "Высота правого поддерева = " << cell->height_right << endl;
		cout << "Балланс = " << cell->balance << endl;
	}
}

vector<Cell*> get_list_auxiliary_function(vector<Cell*> leaves, vector<Cell*> cells, Queue queue, Cell* cell, string mode)
{
	int i, parameter;
	Cell* last_knot = new Cell;
	parameter = 1;
	for (i = 0; i < cells.size(); i++)
		if (cells[i]->value == cell->value)
			parameter = 0;
	if (parameter == 1)
		cells.push_back(cell);
	while (cell->left_ptr != nullptr)
	{
		parameter = 1;
		if (cell->right_ptr != nullptr)
			queue = enqueue(queue, cell->right_ptr);
		cell = cell->left_ptr;
		for (i = 0; i < cells.size(); i++)
			if (cells[i]->value == cell->value)
				parameter = 0;
		if (parameter == 1)
			cells.push_back(cell);
	}
	if (cell->right_ptr != nullptr)
		queue = enqueue(queue, cell->right_ptr);
	else
		leaves.push_back(cell);
	queue = dequeue(queue);
	if (mode == "leaves")
		return leaves;
	if (mode == "all")
		return cells;
}

Tree get_list(Tree tree, string mode)
{
	tree.leaves.clear();
	Queue queue = create();
	queue = enqueue(queue, tree.root);
	while (queue.length != 0)
	{
		if (queue.length != 0)
		{
			if (mode == "leaves")
				tree.leaves = get_list_auxiliary_function(tree.leaves, tree.cells, queue, queue.first->value, mode);
			if (mode == "all")
				tree.cells = get_list_auxiliary_function(tree.leaves, tree.cells, queue, queue.first->value, mode);
			queue = descent(queue, queue.first->value, "");
		}
	}
	return tree;
}

void print_leaves(Tree tree)
{
	tree = get_list(tree, "leaves");
	int i;
	cout << "Листья дерева" << endl;
	for (i = 0; i < tree.leaves.size(); i++)
	{
		cout << tree.leaves[i]->value << endl;
	}
}

Cell* small_left_rorate(Cell* cell)
{
	Cell* c;
	cout << "small_left_rorate " << cell->value << " " << cell->balance << endl;
	c = cell->right_ptr;
	cell->right_ptr->left_ptr->privious_ptr = cell;
	cell->right_ptr = cell->right_ptr->left_ptr;
	c->left_ptr = cell;
	c->privious_ptr = cell->privious_ptr;
	cell->privious_ptr = c;
	return c;
}

Cell* small_right_rorate(Cell* cell)
{
	Cell* c;
	cout << "small_right_rorate " << cell->value << " " << cell->balance << endl;
	c = cell->left_ptr;
	cell->left_ptr->right_ptr->privious_ptr = cell;
	cell->left_ptr = cell->left_ptr->right_ptr;
	c->right_ptr = cell;
	c->privious_ptr = cell->privious_ptr;
	cell->privious_ptr = c;
	return c;
}

Cell* big_left_rorate(Cell* cell)
{
	cout << "big_left_rorate " << cell->value << " " << cell->balance << endl;
	cell->right_ptr = small_right_rorate(cell->right_ptr);
	return small_left_rorate(cell);
}

Cell* big_right_rorate(Cell* cell)
{
	cout << "big_right_rorate " << cell->value << " " << cell->balance << endl;
	cell->right_ptr = small_left_rorate(cell->right_ptr);
	return small_right_rorate(cell);
}

Tree search_for_heights(Tree tree)
{
	int i;
	Cell* cell;
	tree = get_list(tree, "leaves");
	for (i = 0; i < tree.leaves.size(); i++)
	{
		tree.leaves[i]->height_left = tree.leaves[i]->height_right = tree.leaves[i]->balance = 0;
		cell = tree.leaves[i];
		while (cell != tree.root)
		{
			if (cell->privious_ptr->left_ptr == cell)
			{
				if (max(cell->height_left, cell->height_right) + 1 > cell->privious_ptr->height_left)
				{
					cell->privious_ptr->height_left = max(cell->height_left, cell->height_right) + 1;
					cell->privious_ptr->balance = cell->privious_ptr->height_left - cell->privious_ptr->height_right;
				}
			}
			else
			{
				if (max(cell->height_left, cell->height_right) + 1 > cell->privious_ptr->height_right)
				{
					cell->privious_ptr->height_right = max(cell->height_left, cell->height_right) + 1;
					cell->privious_ptr->balance = cell->privious_ptr->height_left - cell->privious_ptr->height_right;
				}
			}
			cell = cell->privious_ptr;
		}
	}
	return tree;
}

Tree balance(Tree tree)
{
	int i;
	Cell* cell;
	for (i = 0; i < tree.cells.size(); i++)
	{
		cell = tree.cells[i];
		if (cell->value != tree.root->value)
		{
			if (cell->balance > 1)
			{
				if (cell->left_ptr->balance >= 0)
					cell = small_right_rorate(cell);
				else
					cell = big_right_rorate(cell);
				search_for_heights(tree);
			}
			if (cell->balance < -1)
			{
				if (cell->right_ptr->balance >= 0)
					cell = small_left_rorate(cell);
				else
					cell = big_left_rorate(cell);
				search_for_heights(tree);
			}
		}
		else
		{
			if (cell->balance > 1)
			{
				if (cell->left_ptr->balance >= 0)
					tree.root = small_right_rorate(tree.root);
				else
					tree.root = big_right_rorate(tree.root);
				search_for_heights(tree);
			}
			if (cell->balance < -1)
			{
				if (cell->right_ptr->balance >= 0)
					tree.root = small_left_rorate(tree.root);
				else
					tree.root = big_left_rorate(tree.root);
				search_for_heights(tree);
			}
		}
	}
	return tree;
}

Cell* append_auxiliary_function(int value, Cell* root)
{
	Cell* cell = new Cell;
	Cell* leaf = new Cell;
	cell = root;
	if ((value <= cell->value) && (cell->left_ptr != nullptr))
	{
		cell = cell->left_ptr;
		cell = append_auxiliary_function(value, cell);
		return cell->privious_ptr;
	}
	else if ((value > cell->value) && (cell->right_ptr != nullptr))
	{
		cell = cell->right_ptr;
		cell = append_auxiliary_function(value, cell);
		return cell->privious_ptr;
	}
	else
	{
		leaf->value = value;
		leaf->left_ptr = nullptr;
		leaf->right_ptr = nullptr;
		if (value <= cell->value)
			cell->left_ptr = leaf;
		else
			cell->right_ptr = leaf;
		leaf->privious_ptr = cell;
		return root;
	}
}

Tree append(Tree tree, int value)
{
	tree.root = append_auxiliary_function(value, tree.root);
	tree.capacity += 1;
	return tree;
}


int main()
{
	setlocale(0, "");
	int i;
	Tree tree;
	tree = create_empty(10);
	tree = append(tree, 5);
	tree = append(tree, 12);
	tree = append(tree, 9);
	tree = append(tree, 3);
	tree = append(tree, 17);
	tree = append(tree, 1);
	tree = append(tree, 8);
	tree = append(tree, 2);
	tree = search_for_heights(tree);
	/*
	tree = get_list(tree, "all");
	tree = balance(tree);
	tree = append(tree, 6);
	tree = append(tree, 4);
	tree = append(tree, 11);
	tree = append(tree, 7);
	tree = search_for_heights(tree);
	*/
	tree.root = small_right_rorate(tree.root);
	tree = search_for_heights(tree);
	print(tree);
	/*поиска элемента в дереве*/
	find_and_info(tree, 10);
}
