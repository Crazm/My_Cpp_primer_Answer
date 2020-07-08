#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	vector<int> num{ 1,2,3,4,5,6,7,8,9 };
	for (auto i = num.rbegin(); i != num.rend(); ++i)
		cout << *i << " ";
	cout << endl;
	for (auto i = num.end(); i != num.begin(); --i)
		cout << *(i-1) << " ";
	return 0;
}