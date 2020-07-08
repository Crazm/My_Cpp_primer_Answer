#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;
using namespace placeholders;

bool check_size(const string &str, unsigned sz) {
	return str.size() >= sz;
}

void biggies(vector<string> &word, unsigned sz) {
	//��word���ֵ�������ɾ���ظ�����
	sort(word.begin(), word.end());
	auto iter = unique(word.begin(), word.end());
	word.erase(iter, word.end());

	//������������ͬ���Ȱ��ֵ�����
	stable_sort(word.begin(), word.end(),
		[](const string &s1, const string &s2)
	{return s1.size() < s2.size(); });

	auto fun = bind(check_size, _1, sz);

	//��ȡһ����������ָ���һ������size()>=sz��Ԫ��
	iter = stable_partition(word.begin(), word.end(),fun);

	//��������size()>sz��Ԫ�ص���Ŀ
	auto count = iter - word.begin();
	cout << "count : " << count << endl;

	//��ӡ���ȴ��ڵ��ڸĶ�ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
	for_each(word.begin(), iter,
		[](const string &s) {cout << s << " "; });
	cout << endl;
}

int main() {
	vector<string> num{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	biggies(num, 4);
	return 0;
}