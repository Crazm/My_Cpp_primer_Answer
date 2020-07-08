#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template <typename T> T calc(T, int);
template <typename T> T fcn(T, T);

int main() {
	double d = 6.28;
	float f = 3.15;
	char c = 'a';
	calc(c, 'c');
	calc(d, f);
	fcn(c, 'c');
	make_shared<vector<int>>();
	return 0;
}