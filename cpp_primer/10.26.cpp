#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	vector<string> str{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	list<string> neew;
	sort(str.begin(), str.end());
	auto unique_end = unique(str.begin(), str.end());
	unique_copy(str.begin(), unique_end, back_inserter(neew));
	str.erase(unique_end, str.end());
	for (auto &i : neew)
		cout << i << " ";
	return 0;
}