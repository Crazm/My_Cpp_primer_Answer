#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace placeholders;

bool check_size(int num, const string &s) {
	return num > s.size();
}

int main() {
	vector<int> num{ 1,2,3,4,5,6,7,8,9 };
	string str{ "hello" };
	auto fun = bind(check_size, _1, str);
	auto n = find_if(num.begin(), num.end(), fun);
	cout << *n << endl;
	return 0;
}