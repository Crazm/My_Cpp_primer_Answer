#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

int main() {
	int a = 10;
	int *p = &a;
	int &cnt = *p;	//ָ��ת����
	cout << cnt << " " << *p << endl;
	int b = 20;
	int &c = b;
	p = &c;			//����תָ��
	cout << c << " " << *p << endl;
	return 0;
}