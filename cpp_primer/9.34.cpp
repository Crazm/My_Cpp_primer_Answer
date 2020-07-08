#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

int main() {

	vector<int> vi{ 0,1,2,3,4,5,6,7,8,9 };
	auto itor = vi.begin();
	while (itor != vi.end()) {
		if (*itor % 2) {
			itor = vi.insert(itor, *itor);
			++itor;
		}
		++itor;
	}
	for (auto &i : vi)
		cout << i << " ";
	return 0;
}