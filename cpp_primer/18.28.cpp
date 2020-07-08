#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct  Base {
	void bar(int){}
protected:
	int ival;
};

struct Derived1 : virtual public Base {
	void bar(char) {}
	void foo(char) {}
protected:
	char cval;
};

struct Derived2 : virtual public Base {
	void foo(int) {}
protected:
	int ival;
	char cval;
};

class VMI : public Derived1, public Derived2 {
	void test(){
		ival = 1;
		cval = 'c';
		foo(32);
		bar('c');
	}
};

int main(){
	return 0;
}