#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
	vector<int> num{ 1,2,3,4,5,6,7,8,9 };
	deque<int> out1, out2, out3;
	copy(num.begin(), num.end(), front_inserter(out1));
	copy(num.begin(), num.end(), back_inserter(out2));
	copy(num.begin(), num.end(), inserter(out3,out3.begin()));
	for (auto &i : out1)
		cout << i << " ";
	cout << endl;
	for (auto &i : out2)
		cout << i << " ";
	cout << endl;
	for (auto &i : out3)
		cout << i << " ";
	cout << endl;

}