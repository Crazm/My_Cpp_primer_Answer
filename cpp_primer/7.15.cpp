#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Person {
	Person() = default;
	Person(istream &is) {
		is >> name >> address;
	}
	Person(const string name,const string address) :
		name(name),address(address){}
	string return_name() const { return name; }
	string return_addr() const { return address; }
	string name;
	string address;
};

istream &read(istream &is, Person &per) {
	is >> per.name >> per.address;
	return is;
}

ostream &print(ostream &os, Person &per) {
	os << per.name << " " << per.address;
	return os;
}

int main() {
	Person per("zhanghua","xianggang"),per1(cin);
	print(cout, per) << endl;
	print(cout, per1) << endl;
	return 0;
}
