#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <map>
#include <set>

using namespace std;

int main() {
	map<string, string::size_type> dictorery;
	string temp;
	while (cin >> temp) {
		for (auto &i : temp)
			if (isupper(i))
				i = tolower(i);
		auto iter = find_if(temp.begin(), temp.end(),
			[](char c) {return ispunct(c); });
		temp.erase(iter);
		auto ret = dictorery.insert({temp,1});
		if (!ret.second)
			++((ret.first)->second);
	}

	for (auto &i : dictorery)
		cout << i.first << " has appear :" << i.second << "time(s)" << endl;
	return 0;
}