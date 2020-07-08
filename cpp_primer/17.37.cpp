#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;

int main() {
	ifstream in("fstest.txt");
	char num[30];
	do {
		in.getline(num, 30);
		cout << num << endl;
	} while (in);
	return 0;
}

//int main() {
//	ifstream in("fstest.txt");
//	char num[20];
//	while (in.getline(num, 20)) {
//		cout << num << endl;
//	}
//	return 0;
//}