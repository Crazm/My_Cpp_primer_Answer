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
	static const pos Screen::* data() {	//˽�г�Ա����һ���������س�Աָ��
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

static const string Sales_data::* data() {	//˽�г�Ա����һ���������س�Աָ��
	return &Sales_data::bookNo;
}

int main() {

	return 0;
}