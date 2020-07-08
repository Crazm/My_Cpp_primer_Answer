#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

vector<int>* dynasty_alloc(void) { return new vector<int>; }

void cintodall(shared_ptr<vector<int>> p) {
	int temp;
	while (cin >> temp)
		p->push_back(temp);
}

void print(shared_ptr<vector<int>> p) {
	for (auto &i : *p)
		cout << i << " ";
}

int main() {
	shared_ptr<vector<int>> p = make_shared<vector<int>>();
	cintodall(p);
	print(p);
	return 0;
}