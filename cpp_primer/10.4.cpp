#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	vector<double> num = { 1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9 };
	double sum = accumulate(num.begin(), num.end(),0.0);
	cout << sum << endl;
	return 0;
}