#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main() {
	cout << boolalpha << true << " " << false << noboolalpha << endl;	
	cout << showbase << dec<< 15 << " " << oct << 15 << " " << hex << 15 << noshowbase << endl;
	cout << showpoint << 3.1 << noshowpoint << endl;
	cout << showpos << 3.14 << noshowpos << endl;	//��ʾ��ֵ������
	cout << uppercase << hex << 15 << nouppercase << endl;	//��16������ʾ��д��0X �Ϳ�ѧ����������ʾE
	cout.precision(3);	//���þ���Ϊ3
	cout << 3.14 << endl;
	cout << 7.1544 << endl;
	cout.precision();
	cout << uppercase << hexfloat << sqrt(2) << endl;
	cout << uppercase << hexfloat << sqrt(3) << endl;
	cout << uppercase << hexfloat << sqrt(4) << endl;
	cout << uppercase << hexfloat << sqrt(5) << endl;
	cout << uppercase << hexfloat << sqrt(6) << endl;
	cout << uppercase << hexfloat << sqrt(7) << endl;
	cout << uppercase << hexfloat << sqrt(4) << endl;
	char ch;
	cin >> noskipws;
	while (cin >> ch)
		cout << ch;
	return 0;
}