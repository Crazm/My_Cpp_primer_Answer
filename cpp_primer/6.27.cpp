#include <iostream>
#include <vector>
#include <string>

using namespace std;
int sum(initializer_list<int> i1)
{
	int sum = 0; 
	for (auto i : i1)
		sum += i;
	return sum;
}

int main(int argc, char *argv[])
{
	cout << sum({ 1,2,3,4,5}) << endl;
	return 0;
}