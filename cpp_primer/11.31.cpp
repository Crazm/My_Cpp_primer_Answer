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
	multimap<string, string> author{ {"sgf","hello"},{"sgf","world"},{"zhangsan","xiaobigha"} };
	auto iter = author.find("sgf");
	if(iter != author.end())
		author.erase(iter);
	for (auto &i : author)
		cout << i.first << " " << i.second << endl;
	return 0;
}