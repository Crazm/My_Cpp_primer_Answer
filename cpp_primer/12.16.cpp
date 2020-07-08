#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

int main() {
	unique_ptr<int> p(new int(55));
	//unique_ptr<int> q = p;
	unique_ptr<int> w(p);
	return 0;
}