#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <fstream>
using namespace std;


int main() {
	string s = "bdfhjlkpq";
	string temp, max;
	ifstream in("string.txt");
	while (in >> temp) {
		if (temp.find(s) == string::npos && temp.size() > max.size()) {
			max = temp;
		}
	}
	cout << max << endl;
	return 0;
}