#include <iostream>
#include <string>
#include <vector>

using namespace std;


class out_of_stock : public runtime_error {
public:
	explicit out_of_stock (const string &s) :runtime_error(s){}
};

class isbn_mismatch :public logic_error {
public:
	explicit isbn_mismatch(const string &s):logic_error(s){}
	isbn_mismatch(const string &s ,const string &lhs, const string &rhs):
		logic_error(s),left(lhs),right(rhs){}
	const string left, right;
};

struct Sales_data {
	Sales_data(const string &s, unsigned u, double r) :
		bookNo(s), units_sold(u), revenue(r) {}
	Sales_data& combine(const Sales_data &rhs) {
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	string isbn() const { return this->bookNo; }
	Sales_data& operator+=(const Sales_data& rhs)
	{
		if (isbn() != rhs.isbn())
			throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
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
	Sales_data S1("hello", 10, 2.99);
	Sales_data S2("world", 10, 3.99);
	try {
		S1 += S2;
	}
	catch (isbn_mismatch &obj) {
		cout << obj.what() << endl;
		cout << "error has done!" << endl;
	}
	cout << "done!" << endl;
	return 0;
}

int main1() {
	Sales_data S1("hello", 10, 2.99);
	Sales_data S2("world", 10, 3.99);
	S1 += S2;
	cout << "done!" << endl;
	return 0;
}
