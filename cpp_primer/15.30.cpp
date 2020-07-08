#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <set>

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
	Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
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
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && { return new Quote(std::move(*this)); }
	virtual ~Quote() = default;	//对析构函数进行动态绑定

private:
	string bookNo;	//书籍的ISBN编号
protected:
	double price = 0.0;	 //代表普通状态下不打折的价格
};

class Bulk_quote : public Quote {	//Bulk_quote继承于类Quote
public:
	Bulk_quote() = default;
	//using Quote::Quote;	//继承Quote的构造函数
	Bulk_quote(string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	Bulk_quote(const Bulk_quote &q) : Quote(q), min_qty(q.min_qty), discount(q.discount) {
		cout << "Bulk_quote(const Bulk_quote &q)拷贝构造函数" << endl;
	}
	Bulk_quote(Bulk_quote &&q) noexcept : Quote(q),
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
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
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

class Basket {
public:
	void add_item(const Quote &sale) {
		items.insert(shared_ptr<Quote>(sale.clone()));
	}
	void add_item(Quote &&sale) {
		items.insert(shared_ptr<Quote>(std::move(sale).clone()));
	}
	double total_receipt(ostream &os) const {
		double sum = 0.0;
		for (auto iter = items.cbegin();
			iter != items.cend();
			iter = items.upper_bound(*iter)) {	//upper_bound返回一个迭代器，指向这批元素的尾后位置
												//iter直接指向下一个关键字，即下一本书籍
			//打印书籍对应的项目
			sum += print_total(os, **iter, items.count(*iter));//count函数统计相同元素的个数
															   //*iter  表示shared_ptr<Quote>
															   //**iter 表示Quote
		}
		os << "Total Sale: " << sum << endl;
		return sum;
	}
private:
	static bool compare(const shared_ptr<Quote> &lhs,
		const shared_ptr<Quote> &rhs)
	{return lhs->isbn() < rhs->isbn();}
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare }; //初始化item并令其使用我们的compare函数
};

int main() {
	Basket bas,bat;
	bas.add_item(Quote("sdf14544", 10));
	bas.add_item(Quote("17105662", 5));
	bat.add_item(Bulk_quote(string("_sdf14544"), 10,2,0.75));
	bat.add_item(Bulk_quote(string("_sdf14544"), 10,2,0.75));
	bat.add_item(Bulk_quote(string("_sdf14544"), 10,2,0.75));
	bas.total_receipt(cout);
	bat.total_receipt(cout);
	return 0;
}
