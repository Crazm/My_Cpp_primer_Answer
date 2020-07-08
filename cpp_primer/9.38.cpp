#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {
	vector<int> num{ 1,2,3,4,5,6,7,8,9,0 };
	cout << "size():" << num.size() << "	"
		<< "capacity()" << num.capacity() << endl;
	for (int i = 0; i < 15; ++i) {
		num.push_back(10 + i);
	}
	cout << "size():" << num.size() << "	"
		<< "capacity()" << num.capacity() << endl;
	for (int i = 0; i < 15; ++i) {
		num.push_back(25 + i);
	}
	cout << "size():" << num.size() << "	"
		<< "capacity()" << num.capacity() << endl;
	return 0;
}