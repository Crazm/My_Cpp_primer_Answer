#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>

using namespace std;

//普通类的成员模板
class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr) :os(s) {}
	//与任何函数模板相同，T的类型由编译器推断
	template <typename T> void operator()(T *p) const
	{
		os << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream &os;
};

class QueryResult;

using line_num = vector<string>::size_type;

class TextQuery {
public:
	TextQuery(ifstream &infile) :file(new vector<string>, DebugDelete()) {	//构造函数要为file分配内存，要不然file为空指针，运行报错
		string temp;
		int i = 1;
		while (getline(infile, temp)) {	//获取文件的每一行
			file->push_back(temp);		//保存此行文本
			istringstream line(temp);	//将行文本以流的形式拆解成单词
			string tem;
			while (line >> tem) {
				if (!ref[tem])				//如果第一次遇到这个单词，要申请内存，并让lines指向这块内存
					ref[tem].reset(new vector<line_num>);
				ref[tem]->push_back(i);	//将行号插入到集合中
			}
			++i;
		}
	}
	QueryResult query(const string &s) const;
private:
	shared_ptr<vector<string>> file;			//保存输入文件的每一行
	map<string, shared_ptr<vector<line_num>>> ref; //保存关键词到所在行号集合的映射
};


class QueryResult {
	friend ostream & print(ostream &out, QueryResult &QR);
public:
	QueryResult(string sou, shared_ptr<vector<string>> fp,
		shared_ptr<vector<line_num>> li) :
		rwords(sou), file(fp), line(li) {}
private:
	string rwords;	//保存当前查询的单词
	shared_ptr<vector<string>> file;	//保存输入文件为指针
	shared_ptr<vector<line_num>> line;		//保存出现的行号
};

QueryResult TextQuery::query(const string &s) const {
	static shared_ptr<vector<line_num>> nofind(new vector<line_num>);//如果未查到，我们返回一个指向此set的指针
	auto i = ref.find(s);   //在map中查找s，如果找到，返回指向s的迭代器，如果找不到返回尾后迭代器
	if (i == ref.end())		//注意，这个迭代器指向的是一个pair类型，->first就是关键词，->second就是对应的值
		return QueryResult(s, file, nofind);
	else
		return QueryResult(s, file, i->second);
}

ostream & print(ostream &out, QueryResult &QR) {
	cout << QR.rwords << " occurs " << QR.line->size()
		<< (QR.line->size() == 1 ? " time" : " times") << endl;
	for (auto num : *QR.line)
		out << "\t(line " << num << ") " << (*(QR.file))[num - 1] << endl;
	return out;
}

void runQueries(ifstream &infile) {
	TextQuery tq(infile);
	string word;
	cout << "Please input research word:";
	cin >> word;
	print(cout, tq.query(word));
	while (1) {
		cout << "enter word to lock for, or q to quit: ";
		string s;
		if (!(cin >> s) || s == "q")
			break;
		print(cout, tq.query(s)) << endl;
	}
}

int main() {
	ifstream in("string.txt");
	runQueries(in);
	return 0;
}