#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

void biggies(vector<string> &word, unsigned sz) {
	//��word���ֵ�������ɾ���ظ�����
	sort(word.begin(), word.end());
	auto iter = unique(word.begin(), word.end());
	word.erase(iter, word.end());

	//������������ͬ���Ȱ��ֵ�����
	stable_sort(word.begin(), word.end(),
		[](const string &s1,const string &s2) 
		{return s1.size() < s2.size();});

	//��ȡһ����������ָ���һ������size()>=sz��Ԫ��
	iter = find_if(word.begin(), word.end(),
		[sz](const string &str) {return str.size() >= sz; });

	//��������size()>sz��Ԫ�ص���Ŀ
	auto count = word.end() - iter;

	//��ӡ���ȴ��ڵ��ڸĶ�ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
	for_each(iter, word.end(),
		[](const string &s) {cout << s << " "; });
	cout << endl;
}

int main() {
	vector<string> num{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	biggies(num, 4);
	return 0;
}
