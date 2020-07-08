#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
	string temp;
	cout << "请输入要打开的文件：";
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
		cout << "无法打开该文件！！！" << endl;
	}
	in.close();
	return 0;
}