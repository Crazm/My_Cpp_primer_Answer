#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	int sz = 99;
	auto f = [sz](int a) {return a + sz; }; //注意：这里的;不能丢
	cout << f(5) << endl;
	return 0;
}
