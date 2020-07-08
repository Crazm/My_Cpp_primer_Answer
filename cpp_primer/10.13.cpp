#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;
bool isup5(const string &s1) {return s1.size() >= 5;}

int main() {
	vector<string> str{ "asd","asdihw","qehiiqe","buadghi","asa","sgf" };
	auto iter = stable_partition(str.begin(), str.end(), isup5);
	for (auto i = str.begin(); i != str.end(); ++i)
		cout << *i << " ";
	return 0;
}