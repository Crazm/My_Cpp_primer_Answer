#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
	vector<string> str;
	string temp;
	ifstream in("fstest.txt");
	if (in) {	//����ļ��Ķ�ȡ�Ƿ�ɹ�,�������õ�ϰ�ߣ�
		while (in >> temp)
			str.push_back(temp);
		for (auto i : str)
			cout << i << endl;
	}
	else {
		cout << "file open fail!!!" << endl;
	}
	in.close();	//�ر��ļ�,ֻ�йر��ļ����ܴ���һ���ļ�
	return 0;
}