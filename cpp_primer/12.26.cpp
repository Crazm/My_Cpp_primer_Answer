#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <cstring>

using namespace std;

int main() {
	allocator<string> alloc;
	string s;
	auto p = alloc.allocate(10);
	auto q = p;
	while (cin >> s && q != p + 10)
		alloc.construct(q++, s);	//构造元素
	for (auto i = p; i != q; ++i)
		cout << *i << endl;
	while (q != p)
		alloc.destroy(--q);//释放我们真正构造的string,此时对应内存并未释放
	alloc.deallocate(p, 10);//释放内存
	return 0;
}