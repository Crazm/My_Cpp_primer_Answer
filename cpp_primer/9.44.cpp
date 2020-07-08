#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

void function(string &s, string &oldval, string&newval) {
	string temp;
	for (auto i=0; i < s.size(); ++i) {
		if (s[i] == oldval[0])
		{
			if (s.size() - i < oldval.size())
				break;
			temp.assign(s.begin()+i, s.begin() + i + oldval.size());
			if (temp == oldval) {
				s.replace(i, oldval.size(), newval);
				i += newval.size() - 1;
			}
		}
	}
}

int main() {
	string str = "123 456 7 8 4 2 3 45 4";
	string old = "4";
	string news = "4456";
	function(str, old, news);
	cout << str << endl;
	return 0;
}