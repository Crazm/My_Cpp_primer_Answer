#include <iostream>
#include <vector>

using namespace std;

union test {	//联合体所有成员都是由低地址存放的
	int i;
	char c;
};

int main() {
	test t;
	t.i = 1;
	if (t.c == 1)	//如果是小端模式，t.c == 0x1
		cout << "小端模式" << endl;
	else			////如果是大端模式，t.c == 0x0
		cout << "大端模式" << endl;
	return 0;
}