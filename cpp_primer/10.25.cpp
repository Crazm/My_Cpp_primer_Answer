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
	//将word按字典序排序，删除重复单词
	sort(word.begin(), word.end());
	auto iter = unique(word.begin(), word.end());
	word.erase(iter, word.end());

	//按长度排序，相同长度按字典排序
	stable_sort(word.begin(), word.end(),
		[](const string &s1, const string &s2)
	{return s1.size() < s2.size(); });

	auto fun = bind(check_size, _1, sz);

	//获取一个迭代器，指向第一个满足size()>=sz的元素
	iter = stable_partition(word.begin(), word.end(),fun);

	//计算满足size()>sz的元素的数目
	auto count = iter - word.begin();
	cout << "count : " << count << endl;

	//打印长度大于等于改定值的单词，每个单词后面接一个空格
	for_each(word.begin(), iter,
		[](const string &s) {cout << s << " "; });
	cout << endl;
}

int main() {
	vector<string> num{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	biggies(num, 4);
	return 0;
}
