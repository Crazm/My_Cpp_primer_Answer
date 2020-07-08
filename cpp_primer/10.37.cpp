#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	vector<int> num{ 0,1,2,3,4,5,6,7,8,9 };
	list<int> out(num.rend() -7, num.rend() - 3);
	for (auto &i : out)
		cout << i << " ";
	cout << endl;
	return 0;
}