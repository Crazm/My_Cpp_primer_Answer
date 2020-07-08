#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double Rate() { return interestRate; }
	static void rate(double);
private:
	string owner;
	double amount;
	static double interestRate;
	static double initRate();
};
