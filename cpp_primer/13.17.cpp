#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>

using namespace std;

static int randnum = 1000000;

class numbered {
	friend void f(const numbered &s);
public:
	numbered() {
		mysn = randnum++;
	}
	numbered(numbered&s) {
		mysn = randnum++;
	}
private:
	int mysn;
};

void f(const numbered &s) {
	cout << s.mysn << endl;
}

int main() {
	numbered a,b = a, c = b;
	f(a);
	f(b);
	f(c);
	return 0;
}