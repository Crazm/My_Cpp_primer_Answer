#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	string str1, str2;
	do {
		cout << "�����������ַ�����";
		cin >> str1 >> str2;
		if (str1.size() < str2.size())
			cout << str1 << endl;
		else
			cout << str2 << endl;
	} while (cin);
	return 0;
}