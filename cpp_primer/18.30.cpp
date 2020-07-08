#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Class {};

class Base :public Class {
public:
	Base() = default;
	Base(const Base &B ):res(B.res){}
	Base(int B):res(B){}
protected:
	int res;
};

class D1 : virtual public Base {
public:
	D1() = default;
	D1(const D1 &B) :Base(B.res) {}
	D1(int B) :Base(B) {}
};

class D2 : virtual public Base {
public:
	D2() = default;
	D2(const D2 &B) : Base(B.res) {}
	D2(int B) : Base(B) {}
};

class MI : public D1, public D2 {
public:
	MI() = default;
	MI(const MI &m) :Base(m.res), D1(m), D2(m) {}
	MI(int i) :Base(i), D1(i), D2(i) {}
};

class Final : public MI, public Class {
public:
	Final() = default;
	Final(const Final &m) :MI(m){}
	Final(int i) :MI(i) {}
};

int main() {

	return 0;
}

//int main() {
//	Base *pb;
//	Class *pc;
//	MI *pmi;
//	D2 *pd2;
//	//pb = new Class;
//	pc = new Final;
//	//pmi = pb;
//	pd2 = pmi;
//	return 0;
//}