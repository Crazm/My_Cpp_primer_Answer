#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	vector<string> str;
	ifstream in("fstest.txt");
	istream_iterator<string> string_it(in);
	istream_iterator<string> string_end;
	ostream_iterator<string> out(cout,"\n");
	while (string_it != string_end)
		str.push_back(*string_it++);
	sort(str.begin(), str.end());
	for (auto &i : str)
		*out++ = i;
	return 0;
}
