#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class Quote {
public:
	Quote() = default;
	Quote(const string &book, double sales_price) :
		bookNo(book), price(sales_price) {}
	string isbn() const { return bookNo; }
	//返回给定数量的销售总额，派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(size_t n) const {
		return n*price;
	}
	virtual ~Quote() = default;	//对析构函数进行动态绑定
	virtual void debug() {
		cout << "ISBN: " << bookNo
			<< " Price: " << price << endl;
	}
private:
	string bookNo;	//书籍的ISBN编号
protected:
	double price = 0.0;	 //代表普通状态下不打折的价格
};

class Bulk_quote : public Quote {	//Bulk_quote继承于类Quote
public:
	Bulk_quote() = default;
	Bulk_quote(string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	double net_price(size_t n) const {
		if (n > min_qty)
			return min_qty * discount * price + (n - min_qty) * price;
		else
			return n * discount * price;
	}
	virtual void debug() {
		cout << "ISBN: " << isbn()
			<< " Price: " << price << " min_qty: " << min_qty
			<< " discount: " << discount << endl;
	}
private:
	size_t min_qty = 0;
	double discount = 0.0;
};

double print_total(ostream &os,
	const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn()
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

int main() {
	Quote quo("sgf", 3.99);
	Bulk_quote bul(string("bulk"), 9.99, 5, 0.75);
	print_total(cout, quo, 10);
	print_total(cout, bul, 10);
	quo.debug();
	bul.debug();
	return 0;
}