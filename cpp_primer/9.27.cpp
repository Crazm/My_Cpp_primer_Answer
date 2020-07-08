#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {
	forward_list<int> num{ 1,2,3,4,5,6,7,8,9 };
	forward_list<int>::iterator pre = num.before_begin();
	forward_list<int>::iterator cur = num.begin();
	while (cur != num.end()) {
		if (*cur % 2)
			cur = num.erase_after(pre);
		else
		{
			pre = cur;
			++cur;
		}
	}
	cur = num.begin();
	while (cur != num.end()) {
		cout << *cur << " ";
		++cur;
	}
		
	return 0;
}