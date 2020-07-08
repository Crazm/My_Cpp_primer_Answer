#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class Shape {
public:
	virtual double square() { return 0; }
};

class circle :public Shape {
public:
	circle(double lg):l(lg){}
	double square() override{
		return 3.14*l*l;
	}
private:
	double l;
};

class Ball :public Shape {
public:
	Ball(double lg) :l(lg) {}
	double square() override {
		return 4/3*3.14*l*l*l;
	}
private:
	double l;
};

int main() {
	circle s(10);
	cout << s.square() << endl;
	return 0;
}