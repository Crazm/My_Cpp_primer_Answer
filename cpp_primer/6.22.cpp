#include <iostream>

using namespace std;

void swap(int **a, int **b)
{
	int * temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	int a =1 , b = 2 ;
	int *i = &a;
	int *j = &b;
	swap(&i, &j);
	cout << "a= " << *i << " b= " << *j << endl;
	return 0;
}