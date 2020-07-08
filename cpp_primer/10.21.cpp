#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	int sz = 10;
	auto f = [&] {return --sz; };
	while (f());
	cout << sz << endl;
	return 0;
}
