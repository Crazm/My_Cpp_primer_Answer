#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

bool islow6(const string &s) { return s.size() >= 6; }

int main() {
	vector<string> vec{ "qwedad","asasascsd","assa","sgf","sasasasqwqe","asasas","ddad","asasegrgrgr" };
	auto cnt = count_if(vec.begin(), vec.end(),islow6);
	cout << cnt << endl;
	return 0;
}