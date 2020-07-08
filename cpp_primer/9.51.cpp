#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

class string2data {
public:
	string2data(string str) {
		string::size_type pos=0;
		while ((pos = str.find_first_of(",/", pos)) != string::npos) {
			str[pos] = ' ';
			++pos;
		}
		istringstream is(str);
		string temp;
		if (isalpha(str[0])) {
			is >> temp >> day >> year;
			for (unsigned i = 0; i < eng.size(); ++i) {
				pos = temp.find(eng[i]);
				if (pos != string::npos) {
					month = i + 1;break;
				}
			}
		}
		else
			is >> month >> day >> year;
	}
	void print() {
		cout << year << '.' << month << '.' << day << endl;
	}
private:
	vector<string> eng{ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec" };
	unsigned year=1995;
	unsigned month=1;
	unsigned day=1;
};

int main() {
	string2data dat1("February 5,1991");
	string2data dat2("1/3/1998");
	string2data dat3("Dec 10 2020");
	dat1.print();
	dat2.print();
	dat3.print();
	return 0;
}