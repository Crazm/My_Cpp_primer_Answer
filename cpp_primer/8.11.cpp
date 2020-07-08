#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Personinfo {
	string name;
	vector<string> phones;
};

int main() {
	string line, word;
	vector<Personinfo> people;
	istringstream record;
	while (getline(cin, line)) {
		Personinfo info;
		record.clear();//循环内部复位
		record.str(line);//循环内部将line拷贝到imm中，返回void
		record >> info.name;
		while (record >> word)
			info.phones.push_back(word);
		people.push_back(info);
	}
	for (auto i : people) {
		cout << i.name << " ";
		for (int j = 0; j != i.phones.size(); ++j)
			cout << i.phones[j] << " ";
		cout << endl;
	}
	return 0;
}