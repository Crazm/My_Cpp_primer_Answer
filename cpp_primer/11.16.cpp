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
	map<string, int> num{ {"zhang",3},{"li",4},{"wang",2},{"sgf",999} };
	map<string, int>::iterator iter =  num.begin();
	while (iter != num.end()) {
			iter->second = 1024;
			++iter;
	}
	for (auto &i : num)
		cout << i.first << " " << i.second << endl;
	return 0;
}