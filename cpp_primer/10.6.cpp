#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std; 

int main() {
	vector<int> num(10);
	fill_n(num.begin(), num.size(), 10);
	for (auto &i : num)
		cout << i << " ";
	return 0;
}