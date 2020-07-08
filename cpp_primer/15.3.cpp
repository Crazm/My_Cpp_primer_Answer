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
	Quote(const string &book,double sales_price):
		bookNo(book),price(sales_price){}
	string isbn() const {return bookNo;}
	//返回给定数量的销售总额，派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(size_t n) const {
		return n*price;
	}
	virtual ~Quote() = default;	//对析构函数进行动态绑定

private:
	string bookNo;	//书籍的ISBN编号
protected:
	double price = 0.0;	 //代表普通状态下不打折的价格
};

class Bulk_quote : public Quote {	//Bulk_quote继承于类Quote
public:
	Bulk_quote() = default;
	Bulk_quote(string &book, double p, size_t qty, double disc) :
	Quote(book,p), min_qty(qty), discount(disc){}
	double net_price(size_t n) const {
		if (n >= min_qty)
			return n * (1 - discount)*price;
		else
			return n * price;
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
	return 0;
}