#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template<typename T>
auto sum(const T &a, const T &b) ->decltype(a + b) {
	return a + b;
}

int main() {
	long long a = 2147483640;
	long long b = 2147483640;
	cout << sum(a, b) << endl;
	return 0;
}