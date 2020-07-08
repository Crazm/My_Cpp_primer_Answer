#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
	vector<string> str;
	string temp;
	ifstream in("fstest.txt");
	if (in) {	//检查文件的读取是否成功,养成良好的习惯！
		while (in >> temp)
			str.push_back(temp);
		for (auto i : str)
			cout << i << endl;
	}
	else {
		cout << "file open fail!!!" << endl;
	}
	in.close();	//关闭文件,只有关闭文件才能打开另一个文件
	return 0;
}