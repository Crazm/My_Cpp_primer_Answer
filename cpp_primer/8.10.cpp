#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
	string temp;
	cout << "������Ҫ�򿪵��ļ���";
	cin >> temp;
	ifstream in(temp);
	if (in) {
		vector<string> vec;
		while (getline(in, temp))
			vec.push_back(temp);
		for (auto i : vec) {
			istringstream is(i);
			while (is >> temp)
				cout << temp << " ";
		}
	}
	else {
		cout << "�޷��򿪸��ļ�������" << endl;
	}
	in.close();
	return 0;
}