#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Sales_data {
	Sales_data& combine(const Sales_data &rhs) {
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	string isbn() const { return this->bookNo; }
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

int main() {
	Sales_data total;
	if (cin >> total.bookNo) {
		Sales_data trans;
		while (cin >> trans.bookNo) {
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				cout << total.bookNo << endl;
				total = trans;
			}
		}
		cout << total.bookNo << endl;
	}
	else {
		cerr << "No data?!" << endl;
		return -1;
	}
	return 0;
}