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
	TextQuery(ifstream &infile) :file(new vector<string>) {	//���캯��ҪΪfile�����ڴ棬Ҫ��ȻfileΪ��ָ�룬���б���
		string temp;
		int i = 1;
		while (getline(infile, temp)) {	//��ȡ�ļ���ÿһ��
			file->push_back(temp);		//��������ı�
			for (auto &i : temp) {
				if (ispunct(i))
					i = ' ';
			}
			istringstream line(temp);	//�����ı���������ʽ���ɵ���
			string tem;
			while (line >> tem) {
				auto &lines = ref[tem];	//lines��һ��shared_ptr<set<line_num>>��ָ��
				if (!lines)				//�����һ������������ʣ�Ҫ�����ڴ棬����linesָ������ڴ�
					lines.reset(new set<line_num>);
				ref[tem]->insert(i);	//���кŲ��뵽������
			}
			++i;
		}
	}
	QueryResult query(const string &s) const;
private:
	shared_ptr<vector<string>> file;			//���������ļ���ÿһ��
	map<string, shared_ptr<set<line_num>>> ref; //����ؼ��ʵ������кż��ϵ�ӳ��
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
	string rwords;	//���浱ǰ��ѯ�ĵ���
	shared_ptr<vector<string>> file;	//���������ļ�Ϊָ��
	shared_ptr<set<line_num>> line;		//������ֵ��к�
};

QueryResult TextQuery::query(const string &s) const {
	static shared_ptr<set<line_num>> nofind(new set<line_num>);//���δ�鵽�����Ƿ���һ��ָ���set��ָ��
	auto i = ref.find(s);   //��map�в���s������ҵ�������ָ��s�ĵ�����������Ҳ�������β�������
	if (i == ref.end())		//ע�⣬���������ָ�����һ��pair���ͣ�->first���ǹؼ��ʣ�->second���Ƕ�Ӧ��ֵ
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

class Query_base {	//������,���ɴ�������
	friend class Query;
protected:
	virtual ~Query_base() = default;
private:
	//eval �����뵱ǰQueryƥ���QueryResult
	virtual QueryResult eval(const TextQuery&) const = 0;	//���麯��
	//rep�Ǳ�ʾ��ѯ��һ��string
	virtual string rep() const = 0;		//���麯��
};

//���ǹ���Query_base�̳���ϵ�Ľӿ���
class Query {
	friend Query operator~(const Query &);
	friend Query operator|(const Query & , const Query &);
	friend Query operator&(const Query &, const Query &);
public:
	Query(string&);		//����һ���µ�wordquery
	//�ӿں��������ö�Ӧ��Query_base����
	QueryResult eval(const TextQuery&t)const
	{
		return q->eval(t);
	}
	string rep() const { return q->rep(); }
	
private:
	Query(shared_ptr<Query_base> query):q(query){}	//˽�еĹ��캯��
	shared_ptr<Query_base> q;
};

class WordQuery :public Query_base {
	friend class Query;
	WordQuery(const string &s): query_word(s){
		//cout << "WordQuery(const string &s)" << endl;
	}
	//������ࣺWordQuery���������м̳ж����Ĵ��麯��
	QueryResult eval(const TextQuery&t)const
	{
		return t.query(query_word);
	}
	string rep() const { return query_word; }
	string query_word;		//Ҫ���ҵĵ���
};

Query::Query(string&s):q(new WordQuery(s)){
	//cout << "Query(string&s)" << endl;
}

class NotQuery:public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q):query(q){
		//cout << "NotQuery(const Query &q)" << endl;
	}
	//������ࣺNotQuery���������м̳ж����Ĵ��麯��
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
	//�����ࣺBinaryQuery ������eval�����̳���eval
	string rep()const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;	//�����Ҳ��������
	string opSym;	//�����������
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &lhs, const Query &rhs) :
		BinaryQuery(lhs, rhs, "&"){
		//cout << "AndQuery(const Query &lhs, const Query &rhs)" << endl;
	}
	//������ࣺAndQuery�̳���rep���Ҷ������������麯��
	QueryResult eval(const TextQuery&)const;
};

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &lhs, const Query &rhs) :
		BinaryQuery(lhs, rhs, "|") {
		//cout << "OrQuery(const Query &lhs, const Query &rhs)" << endl;
	}
	//������ࣺAndQuery�̳���rep���Ҷ������������麯��
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
	//ͨ��Query��Ա��lhs �� rhs���������
	//ͨ��eval����ÿ����������QueryResult
	auto right = rhs.eval(text), left = lhs.eval(text);
	//��������������кſ��������set��
	auto ret_line = make_shared<set<line_num>>(left.begin(), left.end());
	//���Ҳ����������кŲ��뵽���
	ret_line->insert(right.begin(), right.end());
	//����һ���µ�QueryResult����ʾlhs��rhs�Ĳ���
	return QueryResult(rep(),left.get_file(), ret_line );
}

QueryResult AndQuery::eval(const TextQuery&text)const {
	//ͨ��Query��Ա��lhs �� rhs���������,�Ի���������Ĳ�ѯ���set
	auto right = rhs.eval(text), left = lhs.eval(text);
	//��������set��
	auto ret_line = make_shared<set<line_num>>();
	//��������Χ�Ľ���д��һ��Ŀ�ĵ�������
	//���ε��õ�Ŀ�ĵ�������ret_line�����Ԫ��
	set_intersection(left.begin(), left.end()	//set_intersection�����ϲ�����set
		, right.begin(), right.end(),
		inserter(*ret_line, ret_line->begin()));
	//����һ���µ�QueryResult����ʾlhs��rhs�Ĳ���
	return QueryResult(rep(), left.get_file(), ret_line);
}

QueryResult NotQuery::eval(const TextQuery&text)const {
	//ͨ��Query��������eval���������
	auto result = query.eval(text);
	//��ʼʱ���setΪ��
	auto ret_line = make_shared<set<line_num>>();
	//���Ǳ��������������ֵ��������н��е���
	auto beg = result.begin(), end = result.end();
	//���������ļ���ÿһ�У�������в���result�У�������ӵ�ret_line
	auto sz = result.get_file()->size();
	for (size_t n = 1; n <= sz; ++n) {
		if (beg == end || *beg != n)
			ret_line->insert(n);	//�������result���У������һ��
		else if (beg != end)
			++beg;	//�����ȡresult����һ��
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