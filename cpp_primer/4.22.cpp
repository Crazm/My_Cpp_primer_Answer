#include <iostream>
using namespace std;
int main()
{
	int a;
	cin >> a;
	cout << (a > 90 ? "high pass" : a > 75 ? "pass" : a > 60 ? "low pass" : "fail");
	if (a > 90)
		cout << "high pass ";
	else if(a>75)
		cout << "pass ";
	else if(a>60)
		cout << "low pass ";
	else
		cout << "fail ";
	return 0;
}