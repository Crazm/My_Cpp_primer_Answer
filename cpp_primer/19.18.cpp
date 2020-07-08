#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <set>
#include <functional>

using namespace std;

int main() {
	vector<string> vec = { "abc","def","","","gc","" };
	function <bool (const string&)> fcn = &string::empty;
	int num1 = count_if(vec.begin(), vec.end(), mem_fn(&string::empty));
	int num2 = count_if(vec.begin(), vec.end(), fcn);
	int num3 = count_if(vec.begin(), vec.end(), bind(&string::empty, std::placeholders::_1));
	cout << num1 << endl;
	cout << num2 << endl;
	cout << num3 << endl;
	return 0;
}