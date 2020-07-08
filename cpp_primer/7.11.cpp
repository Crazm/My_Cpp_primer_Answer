#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Sales_data {
	Sales_data() = default;
	Sales_data(istream &is)
	{
		double p;
		is >> bookNo >> units_sold >> p;
		revenue = units_sold * p;
	}
	Sales_data(const string &s) :bookNo(s){};
	Sales_data(const string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p*n) {};
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

istream &read(istream &is, Sales_data &item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = item.units_sold * price;
	return is;
}
ostream &print(ostream &os, const Sales_data &item) {
	os << item.bookNo << " " << item.units_sold
		<< " " << item.revenue;
	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

int main() {
	Sales_data total(cin);
	if (cin) {
		Sales_data trans;
		while (read(cin,trans)) {
			if (total.isbn() == trans.isbn())
				total.combine(trans);
			else {
				print(cout, total) << endl;
				total = trans;
			}
		}
		print(cout, total) << endl;
	}
	else {
		cerr << "No data?!" << endl;
		return -1;
	}
	return 0;
}