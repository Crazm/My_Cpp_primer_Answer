#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
using namespace std;

int main() {
	vector<int> num{ 1,2,3,4,5,6,7,8,9 };
	vector<int>::iterator elem1, elem2;
	elem2 = elem1 = num.begin();
	num.erase(elem1, elem2+1);
	cout << num[0] << endl;
	cout << num.at(0) << endl;
	cout << num.front() << endl;
	cout << *num.begin() << endl;
	return 0;
}
