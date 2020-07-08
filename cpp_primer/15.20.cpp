#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class Base {
public:
	void pub_mem(){}
	void memfun(Base &b) { b = *this; }
protected:
	int prot_mem;
private:
	char priv_mem;
};

class Sneaky : public Base {
	void memfun(Base &b) { b = *this; }
	friend void clobber(Sneaky&);
	friend void clobber(Base&);
	int j;		//private
};

struct Pub_derv : public Base {
	void memfun(Base &b) { b = *this; }
	int f() { return prot_mem; }	//派生类能访问protected
	//char g() { return priv_mem; }	//派生类不能访问私有成员
};

struct Priv_derv : private Base {
	void memfun(Base &b) { b = *this; }
	int f1() const { return prot_mem; }	//private不影响派生类的访问权限
};

struct Prot_derv : protected Base {
	void memfun(Base &b) { b = *this; }
	int f1() const { return prot_mem; }	//protected不影响派生类的访问权限
};

//派生访问说明符还可以控制继承自派生类的新类的访问权限
struct Derived_from_public : public Pub_derv {
	void memfun(Base &b) { b = *this; }
	int use_base() { return prot_mem; }
};

struct Derived_from_protected : public Prot_derv {
	void memfun(Base &b) { b = *this; }
	int use_base() { return prot_mem; }
};

struct Derived_from_private : public Priv_derv {
	//void memfun(Base &b) { b = *this; }	//如果D继承B的方式是共有的，或受保护的，则D类的派生类成员和友元可以使用D到B的转化，私有的则不行
	//int use_base() { return prot_mem; }  //prot_mem在Priv_derv中是private的
};

void clobber(Sneaky&s) {
	s.j = s.prot_mem = 0;
}

void clobber(Base&s) {
	//s.prot_mem = 0;	//不能访问Base的保护成员
}

int main() {
	Pub_derv d1;
	Priv_derv d2;
	Prot_derv d3;
	Derived_from_public dd1;
	Derived_from_protected dd2;
	Derived_from_private dd3;
	Base *p = &d1;
	//p = &d2;
	//p = &d3;
	p = &dd1;
	//p = &dd2;
	//p = &dd3;
	return 0;
}