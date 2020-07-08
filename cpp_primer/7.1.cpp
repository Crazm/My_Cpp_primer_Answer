#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Sales_data {
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

int main() {
	Sales_data total;
	if (cin >> total.bookNo) {
		Sales_data trans;
		while (cin >> trans.bookNo) {
			if (total.bookNo == trans.bookNo)
				total.units_sold += 1;
			else {
				cout << total.bookNo << endl;
				total = trans;
			}
		}
		cout << total.bookNo << endl;
	} else {
		cerr << "No data?!" << endl;
		return -1;
	}
	return 0;
}
