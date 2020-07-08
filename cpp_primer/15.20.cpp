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
	int f() { return prot_mem; }	//�������ܷ���protected
	//char g() { return priv_mem; }	//�����಻�ܷ���˽�г�Ա
};

struct Priv_derv : private Base {
	void memfun(Base &b) { b = *this; }
	int f1() const { return prot_mem; }	//private��Ӱ��������ķ���Ȩ��
};

struct Prot_derv : protected Base {
	void memfun(Base &b) { b = *this; }
	int f1() const { return prot_mem; }	//protected��Ӱ��������ķ���Ȩ��
};

//��������˵���������Կ��Ƽ̳��������������ķ���Ȩ��
struct Derived_from_public : public Pub_derv {
	void memfun(Base &b) { b = *this; }
	int use_base() { return prot_mem; }
};

struct Derived_from_protected : public Prot_derv {
	void memfun(Base &b) { b = *this; }
	int use_base() { return prot_mem; }
};

struct Derived_from_private : public Priv_derv {
	//void memfun(Base &b) { b = *this; }	//���D�̳�B�ķ�ʽ�ǹ��еģ����ܱ����ģ���D����������Ա����Ԫ����ʹ��D��B��ת����˽�е�����
	//int use_base() { return prot_mem; }  //prot_mem��Priv_derv����private��
};

void clobber(Sneaky&s) {
	s.j = s.prot_mem = 0;
}

void clobber(Base&s) {
	//s.prot_mem = 0;	//���ܷ���Base�ı�����Ա
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