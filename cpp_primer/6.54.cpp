#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef int(*p)(int, int);

int add(int a, int b) {
	return a + b;
}

int dec(int a, int b) {
	return a - b;
}

int mpy(int a, int b) {
	return a * b;
}

int Div(int a, int b) {
	return a / b;
}

int main() {

	//vector<int(*)(int, int)> fun;
	vector<p> fun = { add ,dec ,mpy ,Div };
	cout << fun[0](1, 2) << endl;
	cout << fun[1](1, 2) << endl;
	cout << fun[2](1, 2) << endl;
	cout << fun[3](1, 2) << endl;

	return 0;
}