#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> a = { 1,2,3,4,5,6,7,8,9};
	for (auto &i : a)
		i = i % 2 == 1 ? 2 * i : i;
	for (auto &i : a)
		cout << i<< " ";
	cout << endl;
	return 0;
}