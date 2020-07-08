#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

map<string, string> buildMAP(ifstream &map_file) {
	map<string, string> temp;
	string key, val;
	while (map_file >> key &&  getline(map_file, val)) {
		//temp[key] = val.substr(1);//返回val的[1:end()];用于去除空格
		temp.insert({ key,val.substr(1) });
	}
	return temp;
}

const string & transform(const string &s, const map<string, string> &m) {

	auto iter = m.find(s);
	if (iter != m.end())
		return iter->second;
	else
		return s;
}

void word_transform(ifstream &mapfile, ifstream &inputfile) {
	map<string, string> maptable = buildMAP(mapfile);
	string line;
	while (getline(inputfile,line)){
		stringstream in(line);
		string word;
		bool sign = true;
		while (in >> word) {
			if (sign)
				sign = false;
			else
				cout << " ";
			cout << transform(word, maptable);
		}
		cout << endl;
	}
}

int main() {
	ifstream mapfile("map.txt");
	ifstream input("input.txt");
	word_transform(mapfile, input);
	return 0;
}