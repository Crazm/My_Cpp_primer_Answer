#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	//�Զ�д�ķ�ʽ�򿪣�����λ���ļ�ĩβ
	fstream inOut("fstest.txt", fstream::ate | fstream::in | fstream::out);
	if (!inOut)
	{
		cout << "���ļ�ʧ��" << endl;
		return EXIT_FAILURE;
	}
	auto end_mark = inOut.tellg();	//��¼ԭ�ļ���βλ��
	inOut.seekg(0, fstream::beg);	//�ٶ�λ���ļ���ͷ
	size_t cnt = 0;			//�ֽ����ۼ���
	string line;			//���������е�ÿһ��
	while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
		cnt += line.size() + 1;	//��һ��ʾ���з�
		auto mark = inOut.tellg();	//��¼��ȡλ��
		inOut.seekp(0, fstream::end);//��д��Ƕ�λ���ļ�β
		inOut << cnt;
		if (mark != end_mark)
			inOut << " ";
		inOut.seekg(mark);	//�ָ���λ�ã�
	}
	inOut.seekp(0, fstream::end);//��д��Ƕ�λ���ļ�β
	inOut << "\n";
	return 0;
}