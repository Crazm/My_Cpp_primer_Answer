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
	auto f = [sz](int a) {return a + sz; }; //ע�⣺�����;���ܶ�
	cout << f(5) << endl;
	return 0;
}
