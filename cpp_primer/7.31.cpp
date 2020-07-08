#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Y;

class X{
	Y *y = nullptr;
};

class Y {
	X x;
};

