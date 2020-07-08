#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
	auto f = [](int a, int b) {return a + b;}; //注意：这里的;不能丢
	cout << f(5, 9) << endl;
	return 0;
}
