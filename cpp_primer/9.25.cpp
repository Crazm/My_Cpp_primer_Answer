#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using namespace std;

int main() {
	int ia[] = { 0,1,1,2,3,5,8,13,21,55,89 };
	vector<int> num1(ia,ia+11);
	vector<int> num2(ia, ia + 11);
	vector<int>::iterator it1 = num1.begin();
	vector<int>::iterator it2 = num2.begin();
	while (it1 != num1.end()) {
		if (*it1 % 2)
			it1 = num1.erase(it1);
		else
			++it1;
	}
	while (it2 != num2.end()) {
		if (*it2 % 2 == 0)
			it2 = num2.erase(it2);
		else
			++it2;
	}
	for (auto &i : num1)
		cout << i << " ";
	cout << endl;
	for (auto &i : num2)
		cout << i << " ";
	cout << endl;
	return 0;
}