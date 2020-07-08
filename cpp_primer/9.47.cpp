#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {
	string str = "ab2c3d7R4E6";
	string nam = "0123456789";
	string::size_type pos = 0;
	while ((pos = str.find_first_not_of(nam, pos)) != string::npos) {
		cout << "index : " << pos << " element is£º " << str[pos] << endl;
		++pos;
	}
	return 0;
}

//int main() {
//	string str = "ab2c3d7R4E6";
//	string nam = "0123456789";
//	string::size_type pos = 0;
//	while ((pos = str.find_first_of(nam, pos)) != string::npos) {
//		cout << "index : " << pos << " element is£º " << str[pos] << endl;
//		++pos;
//	}
//	return 0;
//}