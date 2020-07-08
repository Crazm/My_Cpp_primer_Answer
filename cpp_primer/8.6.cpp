#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Sales_data {
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

int main() {
	string temp;
	cout << "请输入要打开的文件：";
	cin >> temp;
	ifstream in(temp);
	if (in) {
		Sales_data total;
		if (in >> total.bookNo) {
			Sales_data trans;
			while (in >> trans.bookNo) {
				if (total.bookNo == trans.bookNo)
					total.units_sold += 1;
				else {
					cout << total.bookNo << endl;
					total = trans;
				}
			}
			cout << total.bookNo << endl;
		}
		else {
			cerr << "No data?!" << endl;
			return -1;
		}
	}
	else {
		cout << "file open fail!!!" << endl;
	}
	in.close();
	return 0;
}
