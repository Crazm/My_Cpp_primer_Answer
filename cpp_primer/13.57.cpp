#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class Foo {
public:
	Foo sorted()const & {
		cout << "Foo sorted()const &" << endl;
		return Foo(*this).sorted();
	}
	Foo sorted() && {
		sort(data.begin(), data.end());
		cout << "Foo sorted() &&" << endl;
		return *this;
	}
private:
	vector<int> data;
};

int main() {
	Foo().sorted();	//调用 Foo sorted() && 
	Foo b ;
	b.sorted();	//调用sorted()const &
	return 0;
}