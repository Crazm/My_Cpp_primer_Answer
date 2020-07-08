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
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && { return new Quote(std::move(*this)); }
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
			iter = items.upper_bound(*iter)) {	//upper_bound����һ����������ָ������Ԫ�ص�β��λ��
												//iterֱ��ָ����һ���ؼ��֣�����һ���鼮
			//��ӡ�鼮��Ӧ����Ŀ
			sum += print_total(os, **iter, items.count(*iter));//count����ͳ����ͬԪ�صĸ���
															   //*iter  ��ʾshared_ptr<Quote>
															   //**iter ��ʾQuote
		}
		os << "Total Sale: " << sum << endl;
		return sum;
	}
private:
	static bool compare(const shared_ptr<Quote> &lhs,
		const shared_ptr<Quote> &rhs)
	{return lhs->isbn() < rhs->isbn();}
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare }; //��ʼ��item������ʹ�����ǵ�compare����
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
