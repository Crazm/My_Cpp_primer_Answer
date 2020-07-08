#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>
#include <numeric>

using namespace std;

class Sales_data {
	friend istream &read(istream &is, Sales_data &item);	//定义类友元函数
	friend ostream &print(ostream &os, const Sales_data &item);
	friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
public:
	Sales_data() = default;
	Sales_data(const string &s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p*n) {
	};
	Sales_data(istream &is) :Sales_data()
	{
		double p;
		is >> bookNo >> units_sold >> p;
		revenue = units_sold * p;
	}
	Sales_data(const string &s) : Sales_data(s, 0, 0) {}
	Sales_data& combine(const Sales_data &rhs) {
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	string isbn() const { return bookNo; }
private:
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

bool compareIsbn(const Sales_data &s1, const Sales_data &s2) {
	return s1.isbn() < s2.isbn();
}

int main() {
	vector<Sales_data> Sal;
	Sal.emplace_back("zhangsan");
	Sal.emplace_back("lisi");
	sort(Sal.begin(), Sal.end(), 
		[](const Sales_data &s1, const Sales_data &s2)
		{return s1.isbn() < s2.isbn();});
	for (auto &i : Sal)
		cout << i.isbn() << " ";
	return 0;
}