#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

void elimDups(vector<string> &str) {
	sort(str.begin(), str.end());
	auto unique_end = unique(str.begin(), str.end());
	str.erase(unique_end, str.end());
}

bool isShort(const string &s1, const string &s2) {
	return s1.size() < s2.size();
}

int main() {
	vector<string> str;
	string temp;
	while (cin >> temp) {
		str.push_back(temp);
	}
	elimDups(str);
	stable_sort(str.begin(), str.end(), isShort);
	for (auto &i : str)
		cout << i << " ";
	return 0;
}
