#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

vector<int>* dynasty_alloc(void) {return new vector<int>;}

vector<int>* cintodall(vector<int>*p) {
	int temp;
	while (cin >> temp)
		p->push_back(temp);
	return p;
}

void print(vector<int>*p) {
	for (auto &i : *p)
		cout << i << " ";
	delete p;
}

int main() {
	print(cintodall(dynasty_alloc()));
	return 0;
}