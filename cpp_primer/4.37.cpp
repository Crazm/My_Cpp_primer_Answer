#include <iostream>
#include <string>
using namespace std;

int main()
{
	int i;
	double d;
	string str = "123456";
	const string *ps = &str;
	char *pc;
	void *pv;
	++i = 7;
	//pv = reinterpret_cast<void *>(ps);
	i = static_cast<int>(*pc);
	pv = static_cast<void *>(&d);
	pc = reinterpret_cast<char *>(pv);
	return 0;
}
