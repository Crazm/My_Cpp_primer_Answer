#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Person {
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
	Person per;
	read(cin, per);
	print(cout, per);
	return 0;
}
