#include <iostream>
#include <vector>

using namespace std;

union test {	//���������г�Ա�����ɵ͵�ַ��ŵ�
	int i;
	char c;
};

int main() {
	test t;
	t.i = 1;
	if (t.c == 1)	//�����С��ģʽ��t.c == 0x1
		cout << "С��ģʽ" << endl;
	else			////����Ǵ��ģʽ��t.c == 0x0
		cout << "���ģʽ" << endl;
	return 0;
}