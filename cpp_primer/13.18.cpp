#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>

using namespace std;

class Employee {
public:
	Employee() =default;
	Employee(const string &nam):name(nam),ID(ID_rand++) {}
	Employee(const Employee &emp) {
		name = emp.name;
		ID = ID_rand++;
	}
	Employee& operator=(const Employee &rhs) {
		name = rhs.name;
		ID = ID_rand++;
	}
	void print(){
		cout << "name: " << name << " ID: " << ID << endl;
	}
private:
	string name;
	int ID;
	static int ID_rand;
};

int Employee::ID_rand = 1000000; //只能在类外定义，并且不加static

int main() {
	Employee xi("zhangshan"), ha("张华");
	Employee zh(xi);
	Employee zu = ha;
	xi.print();
	ha.print();
	zh.print();
	zu.print();
	return 0;
}
