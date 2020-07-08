#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Base1 {
	void print(int) const {}
protected:
	int ival;
	double dval;
	char cval;
private:
	int *id;
};

struct Base2 {
	void print(double) const{}
protected:
	double fval;
private:
	double dval;
};

struct Derived : public Base1 {
	void print(string) const{}
protected:
	string sval;
	double dval;
};

struct MI : public Derived, public Base2 {
	void print(vector<double>){}
protected:
	int *ival;
	vector<double> dvec;
};

int main() {
	MI mi;
	mi.Derived::Base1::print(42);
	mi.Base1::print(42);
}