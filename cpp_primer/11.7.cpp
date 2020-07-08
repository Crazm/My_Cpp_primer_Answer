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
	map<string, vector<string>> family;
	string temp, first_name, name;
	while (getline(cin, temp)) {
		istringstream in(temp);
		in >> first_name;
		while (in >> name)
			family[first_name].push_back(name);
	}
	for (auto &i : family) {
		cout << i.first << " ";
		for (auto &j : i.second)
			cout << j << " ";
		cout << endl;
	}
	return 0;
}
