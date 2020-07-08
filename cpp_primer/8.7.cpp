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
	cout << "������Ҫ�򿪵��ļ���";
	cin >> temp;
	ifstream in(temp);
	cout << "������Ҫ������ļ���";
	cin >> temp;
	ofstream of(temp, ofstream::out);
	if (in && of) {
		Sales_data total;
		if (in >> total.bookNo) {
			Sales_data trans;
			while (in >> trans.bookNo) {
				if (total.bookNo == trans.bookNo)
					total.units_sold += 1;
				else {
					of << total.bookNo << endl;
					total = trans;
				}
			}
			of << total.bookNo << endl;
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
