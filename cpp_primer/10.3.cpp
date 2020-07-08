#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	vector<int> num = { 1,2,3,4,5,6,7,8,9 };
	int sum = accumulate(num.begin(), num.end(), 0);
	cout << sum << endl;
	return 0;
}