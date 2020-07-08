#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template<unsigned M, unsigned N>
class Screen {
public:
	typedef string::size_type pos;
	Screen() = default;
	Screen(char c) : contents(M*N, c) {}
	char get() const { return contents[cursor]; }	//隐式内联
	inline char get(pos r, pos c);	//显式内联
	inline Screen& move(pos r, pos c) {
		cursor = r * width + c;
		return *this;
	}
	inline Screen& set(char c) {
		contents[cursor] = c;
		return *this;
	}
	inline Screen& set(pos row, pos col, char c) {
		contents[row*width + col] = c;
		return *this;
	}
	Screen& display(ostream &os) {
		do_display(os); return *this;
	}
	template<unsigned mm, unsigned nn>
	friend std::ostream& operator<<(std::ostream &os, const Screen<mm,nn> &s);
	template<unsigned mm, unsigned nn>
	friend std::istream& operator>>(std::istream &is, Screen<mm, nn> &s);

private:
	void do_display(ostream &os) const { os << contents; }
	pos cursor = 0;
	pos height = M, width = N;
	string contents;
};

template<unsigned M, unsigned N>
inline char Screen<M,N>::get(pos r, pos c) {
	return contents[r*width + c];
}

template<unsigned mm, unsigned nn>
std::ostream& operator<<(std::ostream &os, const Screen<mm, nn> &s) {
	for (int i = 0; i != s.height; ++i) {
		for (int j = 0; j != s.width; ++j)
				os << s.contents[i*s.width + j];
		os << '\n';
	}
	return os;	
}

template<unsigned mm, unsigned nn>
std::istream& operator>>(std::istream &is, Screen<mm, nn> &s) {
	string temp;
	is >> temp;
	for (int i = 0; i != temp.size() && i != s.contents.size(); ++i)
		s.contents[i] = temp[i];
	return is;
}


int main() {
	Screen<5, 6> scn('*');
	cin >> scn;
	cout << scn;
	f5(scn);
	return 0;
}
