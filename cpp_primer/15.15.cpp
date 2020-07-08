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

class Disc_quote:public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const string &book,double price,size_t qty,double disc):
	Quote(book,price), quantity(qty), discount(disc){}
	double net_price(size_t) const = 0;
protected:
	size_t quantity = 0;	//折扣适用的购买量
	double discount = 0.0;	//折扣最小数值
};

class Bulk_quote : public Disc_quote {	//Bulk_quote继承于类Quote
public:
	Bulk_quote() = default;
	Bulk_quote(string &book, double p, size_t qty, double disc) :
		Disc_quote(book,p,qty,disc){}
	double net_price(size_t n) const override{
		if (n > quantity)
			return quantity * discount * price + (n - quantity) * price;
		else
			return n * discount * price;
	}
	virtual void debug() {
		cout << "ISBN: " << isbn()
			<< " Price: " << price << " min_qty: " << quantity
			<< " discount: " << discount << endl;
	}
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
	//Disc_quote quo;	//不允许实用抽象类类型的对象
	print_total(cout, quo, 10);
	print_total(cout, bul, 10);
	quo.debug();
	bul.debug();
	return 0;
}