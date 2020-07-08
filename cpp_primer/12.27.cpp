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
	TextQuery(ifstream &infile):file(new vector<string>){	//���캯��ҪΪfile�����ڴ棬Ҫ��ȻfileΪ��ָ�룬���б���
		string temp;
		int i = 1;
		while (getline(infile, temp)) {	//��ȡ�ļ���ÿһ��
			file->push_back(temp);		//��������ı�
			istringstream line(temp);	//�����ı���������ʽ���ɵ���
			string tem;
			while (line >> tem) {
				auto &lines = ref[tem];	//lines��һ��shared_ptr<set<line_num>>��ָ��
				if(!lines)				//�����һ������������ʣ�Ҫ�����ڴ棬����linesָ������ڴ�
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
		shared_ptr<set<line_num>> li):
		rwords(sou),file(fp),line(li){}
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
	cout << QR.rwords << " occurs "<< QR.line->size()
		 <<(QR.line->size()==1?" time":" times") << endl;
	for (auto num : *QR.line)
		out << "\t(line " << num << ") " << (*(QR.file))[num-1] << endl;
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
		print(cout, tq.query(s))<<endl;
	}
}

int main() {
	ifstream in("string.txt");
	runQueries(in);
	return 0;
}