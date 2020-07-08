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
		alloc.construct(q++, s);	//����Ԫ��
	for (auto i = p; i != q; ++i)
		cout << *i << endl;
	while (q != p)
		alloc.destroy(--q);//�ͷ��������������string,��ʱ��Ӧ�ڴ沢δ�ͷ�
	alloc.deallocate(p, 10);//�ͷ��ڴ�
	return 0;
}