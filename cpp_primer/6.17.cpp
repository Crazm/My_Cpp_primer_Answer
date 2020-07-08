#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool IsUpper(const string &s)
{
	for (auto &i : s)
		if (isupper(i))
			return true;
	return false;
}

void lowertoupper(string &s)
{
	for (auto &i : s)
		if (isupper(i))
			i = tolower(i);
}

int main()
{
	string str = "Hello,World\n";
	cout << IsUpper(str) << endl;
	lowertoupper(str);
	cout << str << endl;
	return 0;
}