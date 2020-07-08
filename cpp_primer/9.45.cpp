#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

void function(string &s, string &pre, string&last) {
	s.insert(s.begin(), pre.begin(), pre.end());
	s.insert(s.end(), last.begin(), last.end());
}

//void function(string &s, string &pre, string&last) {
//	s.insert(s.begin(), pre.begin(), pre.end());
//	s.append(last);
//}


int main() {
	string name{ "sgf" };
	string pre = "Mr.";
	string last = "III";
	function(name, pre, last);
	cout << name << endl;
	return 0;
}