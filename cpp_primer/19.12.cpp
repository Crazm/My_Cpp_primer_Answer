#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Screen {
public:
	typedef string::size_type pos;
	char get_cursor() const { return contents[cursor]; }
	char get() const {}
	char get(pos ht, pos wd) const{}
	static const pos Screen::* data() {	//私有成员定义一个函数返回成员指针
		return &Screen::cursor;
	}

	void test() {
		static const pos Screen::*p = data();
		Screen s2;
		auto po = s2.*p;

		auto pmf = &Screen::get_cursor;
		pmf = &Screen::get;

	}
private:
	string contents;
	pos cursor;
	pos height, width;
};

static const string Sales_data::* data() {	//私有成员定义一个函数返回成员指针
	return &Sales_data::bookNo;
}

int main() {

	return 0;
}