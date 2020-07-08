#include <iostream>
#include <vector>
#include <string>

using namespace std;
void print(vector<int> &vec, int n)
{
	if (n-1 > 0)
		print(vec, n - 1);
	cout << vec[n-1] << " ";
}

int main(int argc, char *argv[])
{
	vector<int> vec = {1,2,3,4,5,6,7,8,9,10,11,12};
	print(vec, vec.size());
	return 0;
}