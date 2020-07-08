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
	map<string, vector<pair<string,string>>> family;
	string temp, first_name, name,birthday;
	while (getline(cin, temp)) {
		istringstream in(temp);
		in >> first_name;
		while (in >> name >> birthday)
			family[first_name].emplace_back(name,birthday);
	}
	for (auto &i : family) {
		cout << i.first << " ";
		for (auto &j : i.second)
			cout << j.first << " " << j.second << " ";
		cout << endl;
	}
	return 0;
}