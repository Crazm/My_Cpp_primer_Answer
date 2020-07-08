#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
#include <fstream>
using namespace std;

int main() {
	vector<string> str{ "1","2","3","4","5","6","7" };
	double sum = 0;
	for (auto &i : str) {
		sum += stod(i);
	}
	cout << sum << endl;
	return 0;
}

//int main() {
//	vector<string> str{ "1","2","3","4","5","6","7" };
//	int sum = 0;
//	for (auto &i : str) {
//		sum += stoi(i);
//	}
//	cout << sum << endl;
//	return 0;
//}