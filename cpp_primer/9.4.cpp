#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int>::iterator find(vector<int>::iterator begin, vector<int>::iterator end, int num) {
	bool sign = false;
	auto i = begin;
	for ( ; i != end; ++i)
		if (*i == num) {
			sign = true;
			break;
		}
	if (sign == true)
		return i;
	else
		return end;
}

int main() {
	vector<int> temp{ 1,2,3,4,5,6,7,8,9 };
	vector<int>::iterator res;
	res = find(temp.begin(), temp.end(), 5);
	if (res != temp.end())
		cout << *res << endl;
	else
		cout << " Can't find value!" << endl;
	return 0;
}