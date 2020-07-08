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

class QueryResult;

using line_num = vector<string>::size_type;

class TextQuery {
public:
	TextQuery(ifstream &infile) :file(new vector<string>) {	//构造函数要为file分配内存，要不然file为空指针，运行报错
		string temp;
		int i = 1;
		while (getline(infile, temp)) {	//获取文件的每一行
			file->push_back(temp);		//保存此行文本
			for (auto &i : temp) {
				if (ispunct(i))
					i = ' ';
			}
			istringstream line(temp);	//将行文本以流的形式拆解成单词
			string tem;
			while (line >> tem) {
				auto &lines = ref[tem];	//lines是一个shared_ptr<set<line_num>>的指针
				if (!lines)				//如果第一次遇到这个单词，要申请内存，并让lines指向这块内存
					lines.reset(new set<line_num>);
				ref[tem]->insert(i);	//将行号插入到集合中
			}
			++i;
		}
	}
	QueryResult query(const string &s) const;
private:
	shared_ptr<vector<string>> file;			//保存输入文件的每一行
	map<string, shared_ptr<set<line_num>>> ref; //保存关键词到所在行号集合的映射
};


class QueryResult {
	friend ostream & print(ostream &out, QueryResult &QR);
public:
	QueryResult(string sou, shared_ptr<vector<string>> fp,
		shared_ptr<set<line_num>> li) :
		rwords(sou), file(fp), line(li) {}
	set<line_num>::iterator begin() { return line->begin(); }
	set<line_num>::iterator end() { return line->end(); }
	size_t size() { return line->size(); }
	shared_ptr<vector<string>> get_file() { return file; }
private:
	string rwords;	//保存当前查询的单词
	shared_ptr<vector<string>> file;	//保存输入文件为指针
	shared_ptr<set<line_num>> line;		//保存出现的行号
};

QueryResult TextQuery::query(const string &s) const {
	static shared_ptr<set<line_num>> nofind(new set<line_num>);//如果未查到，我们返回一个指向此set的指针
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

class Query_base {	//抽象类,不可创建对象
	friend class Query;
protected:
	virtual ~Query_base() = default;
private:
	//eval 返回与当前Query匹配的QueryResult
	virtual QueryResult eval(const TextQuery&) const = 0;	//纯虚函数
	//rep是表示查询的一个string
	virtual string rep() const = 0;		//纯虚函数
};

//这是管理Query_base继承体系的接口类
class Query {
	friend Query operator~(const Query &);
	friend Query operator|(const Query & , const Query &);
	friend Query operator&(const Query &, const Query &);
public:
	Query(string&);		//构建一个新的wordquery
	//接口函数：调用对应的Query_base操作
	QueryResult eval(const TextQuery&t)const
	{
		return q->eval(t);
	}
	string rep() const { return q->rep(); }
	
private:
	Query(shared_ptr<Query_base> query):q(query){}	//私有的构造函数
	shared_ptr<Query_base> q;
};

class WordQuery :public Query_base {
	friend class Query;
	WordQuery(const string &s): query_word(s){
		//cout << "WordQuery(const string &s)" << endl;
	}
	//具体的类：WordQuery将定义所有继承而来的纯虚函数
	QueryResult eval(const TextQuery&t)const
	{
		return t.query(query_word);
	}
	string rep() const { return query_word; }
	string query_word;		//要查找的单词
};

Query::Query(string&s):q(new WordQuery(s)){
	//cout << "Query(string&s)" << endl;
}

class NotQuery:public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q):query(q){
		//cout << "NotQuery(const Query &q)" << endl;
	}
	//具体的类：NotQuery将定义所有继承而来的纯虚函数
	QueryResult eval(const TextQuery&)const;
	string rep() const { return "~(" + query.rep() + ")"; }
	Query query;
};

class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query &l, const Query &r, string s):
		lhs(l),rhs(r),opSym(s){
		//cout << "BinaryQuery(const Query &l, const Query &r, string s)" << endl;
	}
	//抽象类：BinaryQuery 不定义eval，但继承了eval
	string rep()const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;	//左侧和右侧运算对象
	string opSym;	//运算符的名字
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &lhs, const Query &rhs) :
		BinaryQuery(lhs, rhs, "&"){
		//cout << "AndQuery(const Query &lhs, const Query &rhs)" << endl;
	}
	//具体的类：AndQuery继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&)const;
};

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &lhs, const Query &rhs) :
		BinaryQuery(lhs, rhs, "|") {
		//cout << "OrQuery(const Query &lhs, const Query &rhs)" << endl;
	}
	//具体的类：AndQuery继承了rep并且定义了其他纯虚函数
	QueryResult eval(const TextQuery&)const;
};

ostream& operator<<(ostream &os, const Query& query) {
	return os << query.rep() << " occurs " ;
}

inline Query operator~(const Query &operand) {
	return shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator&(const Query &lhs, const Query &rhs) {
	return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs) {
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery&text)const {
	//通过Query成员的lhs 和 rhs进行虚调用
	//通过eval返回每个运算对象的QueryResult
	auto right = rhs.eval(text), left = lhs.eval(text);
	//将左侧运算对象的行号拷贝到结果set中
	auto ret_line = make_shared<set<line_num>>(left.begin(), left.end());
	//将右侧运算对象的行号插入到左侧
	ret_line->insert(right.begin(), right.end());
	//返回一个新的QueryResult，表示lhs和rhs的并集
	return QueryResult(rep(),left.get_file(), ret_line );
}

QueryResult AndQuery::eval(const TextQuery&text)const {
	//通过Query成员的lhs 和 rhs进行虚调用,以获得运算对象的查询结果set
	auto right = rhs.eval(text), left = lhs.eval(text);
	//保存结果在set中
	auto ret_line = make_shared<set<line_num>>();
	//将两个范围的交集写在一个目的迭代器中
	//本次调用的目的叠加器向ret_line中添加元素
	set_intersection(left.begin(), left.end()	//set_intersection用来合并两个set
		, right.begin(), right.end(),
		inserter(*ret_line, ret_line->begin()));
	//返回一个新的QueryResult，表示lhs和rhs的并集
	return QueryResult(rep(), left.get_file(), ret_line);
}

QueryResult NotQuery::eval(const TextQuery&text)const {
	//通过Query运算对象对eval进行虚调用
	auto result = query.eval(text);
	//开始时结果set为空
	auto ret_line = make_shared<set<line_num>>();
	//我们必须在运算对象出现的所有行中进行迭代
	auto beg = result.begin(), end = result.end();
	//对于输入文件的每一行，如果该行不在result中，将其添加到ret_line
	auto sz = result.get_file()->size();
	for (size_t n = 1; n <= sz; ++n) {
		if (beg == end || *beg != n)
			ret_line->insert(n);	//如果不在result当中，添加这一行
		else if (beg != end)
			++beg;	//否则获取result的下一行
	}
	return QueryResult(rep(), result.get_file(), ret_line);
}

int main() {
	ifstream in("string.txt");
	TextQuery tq(in);
	//Query q = Query(string("fiery")) & Query(string("bird")) | Query(string("wind"));
	//print(cout, q.eval(tq));
	Query q = Query(string("Daddy"));
	print(cout, q.eval(tq));
	Query v = ~Query(string("Alice"));
	print(cout, v.eval(tq));
	Query w = Query(string("Alice")) | Query(string("hair"));
	print(cout, w.eval(tq));
	Query u = Query(string("Alice")) & Query(string("hair"));
	print(cout, u.eval(tq));
	Query z = Query(string("fiery")) & Query(string("bird")) | Query(string("wind"));
	print(cout, z.eval(tq));
	return 0;
}