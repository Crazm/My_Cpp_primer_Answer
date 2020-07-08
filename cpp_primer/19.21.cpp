#include <iostream>
#include <string>

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
	Sales_data(const Sales_data &s) : 
		bookNo(s.bookNo),units_sold(s.units_sold),revenue(s.revenue) {}
	Sales_data(istream &is) :Sales_data()
	{
		double p;
		is >> bookNo >> units_sold >> p;
		revenue = units_sold * p;
	}
	Sales_data(const string &s) : Sales_data(s, 0, 0) {}
	Sales_data& operator=(const Sales_data&rhs) {
		bookNo = rhs.bookNo;
		units_sold = rhs.units_sold;
		revenue = rhs.revenue;
		return *this;
	}
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

class Token {
	friend ostream& operator<<(ostream &os, const Token &t);
public:
	Token():tok(INT),ival{0}{}
	Token(const Token &t) :tok(t.tok) { copyUnion(t); }
	Token(Token &&t):tok(std::move(t.tok)) {
		moveUnion(std::move(t));
	}
	Token &operator=(Token &&t) {
		if (this != &t) {
			this->~Token();
			tok = std::move(t.tok);
			moveUnion(std::move(t));
		}
		return *this;
	}
	Token &operator=(const Token&);
	~Token() {
		if (tok == STR )
			sval.~string(); 
		if (tok == SAL)
			sale.~Sales_data();
	}
	Token &operator=(const string&);
	Token &operator=(char);
	Token &operator=(int);
	Token &operator=(double);
	Token &operator=(Sales_data&);
	void moveUnion(Token &&t) {
		switch (t.tok) {
		case Token::INT:  ival = std::move(t.ival); break;
		case Token::CHAR: cval = std::move(t.cval); break;
		case Token::DBL:  dval = std::move(t.dval); break;
		case Token::STR:  new(&sval) string(std::move(t.sval)); break;
		case Token::SAL:  new(&sale) Sales_data(std::move(t.sale)); break;
		}
	}
private:
	enum{INT,CHAR,DBL,STR,SAL} tok;
	union {
		char cval;
		int ival;
		double dval;
		string sval;
		Sales_data sale;
	};
	void copyUnion(const Token&);
};

Token &Token::operator=(int i) {
	if (tok == STR) sval.~string();
	ival = i;
	tok = INT;
	return *this;
}

Token &Token::operator=(char c) {
	if (tok == STR) sval.~string();
	cval = c;
	tok = CHAR;
	return *this;
}

Token &Token::operator=(double d) {
	if (tok == STR) sval.~string();
	dval = d;
	tok = DBL;
	return *this;
}

Token &Token::operator=(const string&s) {
	if (tok == STR)
		sval = s;
	else
		new(&sval) string(s);
	tok = STR;
	return *this;
}

Token &Token::operator=(Sales_data &s) {
	if (tok == SAL)
		sale = s;
	else
		new(&sale) Sales_data(s);
	tok = SAL;
	return *this;
}

void Token::copyUnion(const Token &t) {
	switch (t.tok) {
	case Token::INT:  ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL:  dval = t.dval; break;
	case Token::STR:  new(&sval) string(t.sval); break;
	case Token::SAL:  new(&sale) Sales_data(t.sale); break;
	}
}

Token & Token::operator=(const Token &t) {
	if (tok == STR && t.tok != STR)
		sval.~string();
	if (tok == STR && t.tok == STR)
		sval = t.sval;
	if (tok == SAL && t.tok != SAL)
		sale.~Sales_data();
	if (tok == SAL && t.tok == SAL)
		sale = t.sale;
	else
		copyUnion(t);
	tok = t.tok;
	return *this;
}

ostream& operator<<(ostream &os, const Token &t) {
	switch (t.tok) {
	case Token::INT:  os << t.ival; break;
	case Token::CHAR: os << t.cval; break;
	case Token::DBL:  os << t.dval; break;
	case Token::STR:  os << t.sval; break;
	case Token::SAL:  os << t.sale.isbn(); break;
	}
	return os;
}

int main()
{
	using namespace std;
	string s = "string";
	Sales_data item("c++ primer 5", 12, 128.0);
	int i = 12;
	char c = 'c';
	double d = 1.28;
	Token t;
	t = i;
	cout << t << "\t";
	t = c;
	cout << t << "\t";
	t = d;
	cout << t << "\t";
	t = s;
	cout << t << "\t";
	t = item;
	cout << t << endl;
	Token t2 = t;
	cout << t2 << "\t";
	t2 = s;
	cout << t2 << "\t";
	t2 = t;
	cout << t2 << "\t";
	t2 = c;
	cout << t2 << "\t";
	t = s;
	t2 = std::move(t);
	cout << t2 << endl;
	Token t3 = std::move(t2);
	cout << t3 << "\t";
	t3 = t3;
	cout << t3 << "\t";
	t3 = item;
	cout << t3 << endl;
	t2 = std::move(t3);
	cout << t2 << endl;
	system("pause");
	return 0;
}