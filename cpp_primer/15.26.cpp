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
	Quote(const Quote &q) :bookNo(q.bookNo), price(q.price) {
		cout << "Quote(const Quote &q)拷贝构造函数" << endl;
	}
	Quote(Quote &&q) noexcept:bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
		cout << "Quote(Quote &&q)移动构造函数" << endl;
	}
	Quote& operator=(const Quote &rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
		cout << "Quote& operator=拷贝赋值运算符" << endl;
		return *this;
	}
	Quote& operator=(Quote &&rhs) {
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
		cout << "Quote& operator=移动赋值运算符" << endl;
		return *this;
	}
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
	using Quote::Quote;	//继承Quote的构造函数
	Bulk_quote(string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	Bulk_quote(const Bulk_quote &q) : Quote(q), min_qty(q.min_qty),discount(q.discount){
		cout << "Bulk_quote(const Bulk_quote &q)拷贝构造函数" << endl;
	}
	Bulk_quote(Bulk_quote &&q) noexcept :Quote(q),
	min_qty(std::move(q.min_qty)), discount(std::move(q.discount)) {
		cout << "Bulk_quote(Bulk_quote &&q)移动构造函数" << endl;
	}
	Bulk_quote& operator=(const Bulk_quote &rhs) {
		Quote::operator=(rhs);		//为基类赋值
		min_qty = rhs.min_qty;
		discount = rhs.discount;
		cout << "Bulk_quote& operator=拷贝赋值运算符" << endl;
		return *this;
	}
	Bulk_quote& operator=(Bulk_quote &&rhs) {
		Quote::operator=(rhs);		//为基类赋值
		min_qty = std::move(rhs.min_qty);
		discount = std::move(rhs.discount);
		cout << "移动赋值运算符" << endl;
		return *this;
	}
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
	Quote ihs(bul);
	Quote auo;
	auo = bul;
	Quote qwe(std::move(bul));
	print_total(cout, quo, 10);
	print_total(cout, bul, 10);
	return 0;
}