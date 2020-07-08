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
	multimap<string, string> author{ { "sgf","hello" },{ "sgf","world" },{ "zhangsan","xiaobigha" } };
	auto iter1 = author.lower_bound("sgf");
	auto iter2 = author.upper_bound("sgf");
	for (; iter1 != iter2; ++iter1)
		cout << iter1->first << " " << iter1->second << endl;
	return 0;
}