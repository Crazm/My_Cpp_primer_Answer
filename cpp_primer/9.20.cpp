#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using namespace std;

int main() {

	list<int> num{ 1,2,3,4,5,6,7,8,9 };
	deque<int> deq1, deq2;
	for (auto &i : num) {
		if (i % 2 == 0)
			deq1.push_back(i);
		else
			deq2.push_back(i);
	}
	for (auto &i : deq1)
		cout << i << " ";
	for (auto &i : deq2)
		cout << i << " ";
	return 0;
}