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
	multimap<string, string> family;
	string temp, first_name, name;
	while (getline(cin, temp)) {
		istringstream in(temp);
		in >> first_name;
		while (in >> name)
			family.insert({ first_name,name });
	}
	for (auto &i : family) {
		cout << i.first << " " << i.second << endl;
	}
	return 0;
}
