#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Person {
	string return_name() const { return name;}
	string return_addr() const { return address; }
	string name;
	string address;
};

int main() {
	Person per;
	per.name = "xiaoming";
	per.address = "huanggong";
	cout << per.return_name() << endl;
	cout << per.return_addr() << endl;
	return 0;
}