#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
	vector<int> num{ 1,1,2,3,41,2,3,4,41,12,4,41,3,5,6,7,89,1,2,3,4,5,6 };
	cout << count(num.begin(), num.end(), 1) << endl;
	list<string> str{ "123","456","123","098","12" };
	cout << count(str.begin(), str.end(), "123") << endl;
	return 0;
}
