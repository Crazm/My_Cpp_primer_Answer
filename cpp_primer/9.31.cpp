#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {

	forward_list<int> vi{ 0,1,2,3,4,5,6,7,8,9 };
	auto pre = vi.before_begin();
	auto cur = vi.begin();
	while (cur != vi.end()) {
		if (*cur % 2) {
			vi.insert_after(pre, *cur);
			pre = cur;
			++cur;
		}
		else
			cur = vi.erase_after(pre);

	}
	for (auto &i : vi)
		cout << i << " ";
	return 0;
}

//int main() {
//
//	list<int> vi{ 0,1,2,3,4,5,6,7,8,9 };
//	auto iter = vi.begin();
//	while (iter != vi.end()) {
//		if (*iter % 2) {
//			iter = vi.insert(iter, *iter);
//			++iter;
//			++iter;
//		}
//		else
//			iter = vi.erase(iter);
//	}
//	for (auto &i : vi)
//		cout << i << " ";
//	return 0;
//}