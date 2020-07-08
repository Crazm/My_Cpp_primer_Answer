#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int main(){
	list<int> my{ 1,2,4,5,6 };
	vector<int> my1{ 1,2,3,4,5,6 };
	vector<double> d(my.begin(), my.end());
	vector<double> d1(my1.begin(), my1.end());
	return 0;
}
