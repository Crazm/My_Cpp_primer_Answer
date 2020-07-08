#include <iostream>
#include <vector>
#include <string>

using namespace std;

void reset(int &n)
{
	n = 0;
}

int main()
{
	int  i = 99;
	reset(i);
	cout << i << endl;
	return 0;
}