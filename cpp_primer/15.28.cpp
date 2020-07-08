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
	//���ظ��������������ܶ�����ฺ���д��ʹ�ò�ͬ���ۿۼ����㷨
	Quote(const Quote &q) :bookNo(q.bookNo), price(q.price) {
		cout << "Quote(const Quote &q)�������캯��" << endl;
	}
	Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
		cout << "Quote(Quote &&q)�ƶ����캯��" << endl;
	}
	Quote& operator=(const Quote &rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
		cout << "Quote& operator=������ֵ�����" << endl;
		return *this;
	}
	Quote& operator=(Quote &&rhs) {
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
		cout << "Quote& operator=�ƶ���ֵ�����" << endl;
		return *this;
	}
	virtual double net_price(size_t n) const {
		return n*price;
	}
	virtual ~Quote() = default;	//�������������ж�̬��

private:
	string bookNo;	//�鼮��ISBN���
protected:
	double price = 0.0;	 //������ͨ״̬�²����۵ļ۸�
};

class Bulk_quote : public Quote {	//Bulk_quote�̳�����Quote
public:
	Bulk_quote() = default;
	//using Quote::Quote;	//�̳�Quote�Ĺ��캯��
	Bulk_quote(string &book, double p, size_t qty, double disc) :
		Quote(book, p), min_qty(qty), discount(disc) {}
	Bulk_quote(const Bulk_quote &q) : Quote(q), min_qty(q.min_qty), discount(q.discount) {
		cout << "Bulk_quote(const Bulk_quote &q)�������캯��" << endl;
	}
	Bulk_quote(Bulk_quote &&q) noexcept : Quote(q),
		min_qty(std::move(q.min_qty)), discount(std::move(q.discount)) {
		cout << "Bulk_quote(Bulk_quote &&q)�ƶ����캯��" << endl;
	}
	Bulk_quote& operator=(const Bulk_quote &rhs) {
		Quote::operator=(rhs);		//Ϊ���ำֵ
		min_qty = rhs.min_qty;
		discount = rhs.discount;
		cout << "Bulk_quote& operator=������ֵ�����" << endl;
		return *this;
	}
	Bulk_quote& operator=(Bulk_quote &&rhs) {
		Quote::operator=(rhs);		//Ϊ���ำֵ
		min_qty = std::move(rhs.min_qty);
		discount = std::move(rhs.discount);
		cout << "�ƶ���ֵ�����" << endl;
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
	vector<Quote> basket;
	basket.push_back(Quote("0123456789", 50));
	basket.push_back(Bulk_quote(string("021123-45-564"),50,10,0.25));
	cout << basket.back().net_price(15) << endl;//���õ��ǻ����net_price,���750
	
	vector<shared_ptr<Quote>> basptr;
	basptr.push_back(make_shared<Quote>("0123456789", 50));
	basptr.push_back(make_shared<Bulk_quote>(string("021123-45-564"), 50, 10, 0.25));
	cout << basptr.back()->net_price(15) << endl;
	return 0;
}