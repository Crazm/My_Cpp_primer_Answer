#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

void func(forward_list<string> &list, string &str1, string &str2) {
	forward_list<string>::iterator pre = list.before_begin();
	forward_list<string>::iterator cur = list.begin();
	while (cur != list.end()) {
		if (*cur == str1)
			break;
		else
		{
			pre = cur;
			++cur;
		}
	}
	if (cur != list.end())
		list.insert_after(cur, str2);
	else
		list.insert_after(pre, str2);
}

int main() {
	forward_list<string> list{ "sgf","abc","123","456" };
	func(list, string("abd"), string("good"));
	forward_list<string>::iterator cur = list.begin();
	while (cur != list.end()) {
		cout << *cur << " ";
		++cur;
	}

	return 0;
}