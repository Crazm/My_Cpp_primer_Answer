#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main() {
	vector<int> a{ 1,2,3 };
	vector<int> b{ 1,2,3 };
	
	list<int> c{ 1,2,3 };
	cout << (a == b) << endl;
	cout << (a == c) << endl;
	return 0;
}