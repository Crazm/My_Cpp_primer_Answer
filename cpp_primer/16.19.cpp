#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

//template<typename T>
//void print(T &t) {
//	for (std::size_t i = 0; i != t.size(); ++i)
//		cout << t[i] << endl;
//}/*19Ìâ*/

template<typename T>
void print(T &t) {
	for (T::iterator beg = t.begin(); beg != t.end(); ++beg)
		cout << *beg << endl;
}/*20Ìâ*/

int main() {
	vector<int> vec = { 1,2,3,4,5,6,7 };
	print(vec);
	return 0;
}