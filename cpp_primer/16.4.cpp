#include <iostream>
#include <vector>
#include <string>
#include "TEMPLATE.h"
#include <list>

using namespace std;

int main() {
	vector<int> vec{1,2,3,4,5,6,7,8,9};
	int num[] = { 1,2,3,4,5,6,7,8,9 };
	string str[] = { "123","456","789" };
	list<string> lis{ "123","456","789" };
	cout << Find(vec.begin(), vec.end(),1) << endl;
	cout << Find(lis.begin(), lis.end(), "123") << endl;
	cout << *begin(str) << endl;
	cout << *(end(str) - 1) << endl;
	cout << Size(str) << endl;
	return 0;
}
