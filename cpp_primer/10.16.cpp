#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

void biggies(vector<string> &word, unsigned sz) {
	//将word按字典序排序，删除重复单词
	sort(word.begin(), word.end());
	auto iter = unique(word.begin(), word.end());
	word.erase(iter, word.end());

	//按长度排序，相同长度按字典排序
	stable_sort(word.begin(), word.end(),
		[](const string &s1,const string &s2) 
		{return s1.size() < s2.size();});

	//获取一个迭代器，指向第一个满足size()>=sz的元素
	iter = find_if(word.begin(), word.end(),
		[sz](const string &str) {return str.size() >= sz; });

	//计算满足size()>sz的元素的数目
	auto count = word.end() - iter;

	//打印长度大于等于改定值的单词，每个单词后面接一个空格
	for_each(iter, word.end(),
		[](const string &s) {cout << s << " "; });
	cout << endl;
}

int main() {
	vector<string> num{ "the","quick","red","fox","jumps","over","the","slow","red","turtle" };
	biggies(num, 4);
	return 0;
}
