#include <iostream>
#include <vector>
#include <string>

using namespace std;

void swap(int &i,int &j)
{
	int temp = i;
	i = j;
	j = temp;
}

int main()
{
	int a = 10, b = 20;
	swap(a, b);
	cout << "a= " << a << " ,b= " << b << endl;
	return 0;
}