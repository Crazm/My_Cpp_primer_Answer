#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	list<int> num{ 1,2,3,4,5,6,7,8,0,9 };
	auto i = find(num.rbegin(),num.rend(), 0);
	cout << *i << endl;
	return 0;
}