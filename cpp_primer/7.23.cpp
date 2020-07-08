#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Screen {
public:
	typedef string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd) :height(ht), width(wd), contents(ht*wd, ' ') {}
	Screen(pos ht, pos wd, char c):height(ht),width(wd),contents(ht*wd,c){}
	char get() const { return contents[cursor];}	//隐式内联
	inline char get(pos r, pos c);	//显式内联
	inline Screen& move(pos r, pos c) {
		cursor = r * width + c;
		return *this;
	}
	inline Screen& set(char c) {
		contents[cursor] =  c;
		return *this;
	}
	inline Screen& set(pos row,pos col,char c) {
		contents[row*width +col] = c;
		return *this;
	}
	Screen& display(ostream &os){
		do_display(os);return *this;}
	const Screen& display(ostream &os) const  {
		do_display(os);return *this;}


private:
	void do_display(ostream &os) const {os << contents;}
	pos cursor = 0;
	pos height = 0, width = 0;
	string contents;
};

inline char Screen::get(pos r, pos c) {
	return contents[r*width+c];
}

int main() {
	Screen myscreen(5, 5, 'X');
	myscreen.move(4, 0).set('#').display(cout);
	cout << endl;
	myscreen.display(cout);
	cout << endl;
	return 0;
}
