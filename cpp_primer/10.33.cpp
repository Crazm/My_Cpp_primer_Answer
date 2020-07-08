#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

int main() {
	ifstream in("num.txt");
	if (!in)	return -1;
	ofstream odd("num_odd.txt"), even("num_even.txt");
	istream_iterator<int> int_it(in), it_end;
	ostream_iterator<int> out1(odd, " "), out2(even, "\n");
	while (int_it != it_end) {
		if (*int_it % 2)
			out1 = *int_it++;
		else
			out2 = *int_it++;
	}
	return 0;
}