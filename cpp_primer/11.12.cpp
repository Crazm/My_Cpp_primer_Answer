#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <map>
#include <set>
#include <utility>

using namespace std;

int main() {
	vector<pair<string, int>> num;
	string temp;
	int n;
	while (cin >> temp >> n)
		num.emplace_back(temp,n);
		//num.push_back({ temp,n });
		//num.push_back(make_pair( temp,n ));
		//num.push_back(pair<string, int>(temp,n));
		
	for (auto &i : num)
		cout << i.first << " " << i.second << endl;
	return 0;
}