#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(int *k, int len)
{
	for (int i = 0; i < len; ++i)
		cout << k[i] << " ";
	cout << endl;
}

void print(int *beg, int* end)
{
	for (; beg < end; ++beg)
		cout << *beg << " ";
	cout << endl;
}

int main()
{
	int i = 0, j[2] = { 0,1 };
	print(&i, 1);
	print(j, 2);
	print(begin(j), end(j));
	return 0;
}