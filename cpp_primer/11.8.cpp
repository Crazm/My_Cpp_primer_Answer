#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int main() {
	vector<string> str;
	string temp;
	while (cin >> temp) {
		if (find(str.begin(), str.end(), temp) == str.end())
			str.push_back(temp);
	}
	for (auto &i : str)
		cout << i << " ";
	return 0;
}