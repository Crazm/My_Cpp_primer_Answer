#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
using namespace std;

void function(string &s, string &oldval, string&newval) {
	string temp;
	for (auto iter = s.begin(); iter != s.end(); ++iter) {
		if (*iter == oldval[0])
		{
			if (static_cast<unsigned>(s.end() - iter) < oldval.size())
				break;
			temp.assign(iter, iter + oldval.size());
			if (temp == oldval) {
				iter = s.erase(iter, iter + oldval.size()); //���ص������һ����ɾ����Ԫ�ص���һ��λ��
				iter = s.insert(iter,newval.begin(), newval.end());//���ص��ǲ����Ԫ�صĵ�һ��λ��
				iter += newval.size() -1;
			}
			if (iter == s.end())
				break;
		}
	}
}

int main() {
	string str = "123 456 7 8 4 2 3 45 4";
	string old = "45";
	string news = "4456";
	function(str, old, news);
	cout << str << endl;
	return 0;
}