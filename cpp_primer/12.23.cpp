#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <cstring>

using namespace std;

int main() {
	string st1 = "shello ";
	string st2 = "sworld!";
	st1 += st2;
	char *s1 = "hello ";
	char *s2 = "world!";
	char *p = new char[strlen(s1)+strlen(s2)];
	strcpy(p, s1);
	strcat(p, s2);
	cout << p << endl;
	char *q = new char[st1.size()];
	strcpy(q, st1.c_str());
	cout << q << endl;
	return 0;
}