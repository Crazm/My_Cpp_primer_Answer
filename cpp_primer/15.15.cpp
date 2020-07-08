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
	virtual double net_price(size_t n) const {
		return n*price;
	}
	virtual ~Quote() = default;	//�������������ж�̬��
	virtual void debug() {
		cout << "ISBN: " << bookNo
			<< " Price: " << price << endl;
	}
private:
	string bookNo;	//�鼮��ISBN���
protected:
	double price = 0.0;	 //������ͨ״̬�²����۵ļ۸�
};

class Disc_quote:public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const string &book,double price,size_t qty,double disc):
	Quote(book,price), quantity(qty), discount(disc){}
	double net_price(size_t) const = 0;
protected:
	size_t quantity = 0;	//�ۿ����õĹ�����
	double discount = 0.0;	//�ۿ���С��ֵ
};

class Bulk_quote : public Disc_quote {	//Bulk_quote�̳�����Quote
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
	//Disc_quote quo;	//������ʵ�ó��������͵Ķ���
	print_total(cout, quo, 10);
	print_total(cout, bul, 10);
	quo.debug();
	bul.debug();
	return 0;
}