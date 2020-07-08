#include <iostream>
#include <vector>
#include <string>
#include "Chapter6.h"
using namespace std;

long long fact(int n) {
	long long val=1;
	while (n>1)
		val *= n--;
	return val;
}