#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A {
public:
	A() {
		cout << "A" << endl;
	}
};

class B: public A {
public:
	B() {
		cout << "B" << endl;
	}
};

class C : public B {
public:
	C() {
		cout << "C" << endl;
	}
};

class X {
public:
	X() {
		cout << "X" << endl;
	}
};

class Y {
public:
	Y() {
		cout << "Y" << endl;
	}
};

class Z :public X, public Y {
public:
	Z() {
		cout << "Z" << endl;
	}
};

class MI :public C, public Z {
public:
	MI() {
		cout << "MI" << endl;
	}
};

int main() {
	MI mi;
	return 0;
}

