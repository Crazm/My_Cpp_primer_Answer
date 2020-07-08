#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {
	vector<char> strr{ '1','2','3','4' };
	string str(strr.begin(),strr.end());
	cout << str;
	return 0;
}