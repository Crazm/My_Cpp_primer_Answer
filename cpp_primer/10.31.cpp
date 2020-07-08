#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	ifstream in("fstest.txt");
	istream_iterator<string> string_it(in),string_end;
	ostream_iterator<string> out(cout, "\n");
	vector<string> str(string_it, string_end),outstr;
	sort(str.begin(), str.end());
	unique_copy(str.begin(), str.end(), back_inserter(outstr));
	for (auto &i : outstr)
		*out++ = i;
	return 0;
}
