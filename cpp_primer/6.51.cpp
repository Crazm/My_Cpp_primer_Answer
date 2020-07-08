#include <iostream>
#include <vector>
#include <string>

using namespace std;

void fun()
{
	cout << "fun()" << endl;
}

void fun(int a)
{
	cout << "fun(int)" << endl;
}

void fun(int a, int b)
{
	cout << "fun(int ,int)" << endl;
}

void fun(double a, double b)
{
	cout << "fun(double,double)" << endl;
}

int main(int argc, char *argv[])
{
//	fun(2.56, 42);
	fun(40);
	fun(42, 0);
	fun(2.56, 3.14);
	return 0;
}