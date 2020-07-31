#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

int main() {
	int a = 10;
	int *p = &a;
	int &cnt = *p;	//指针转引用
	cout << cnt << " " << *p << endl;
	int b = 20;
	int &c = b;
	p = &c;			//引用转指针
	cout << c << " " << *p << endl;
	return 0;
}