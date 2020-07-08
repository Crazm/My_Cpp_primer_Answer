#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main(int argc, char *argv[])
{
	string s1 = argv[0], s2 ="123";
	s1 += s2;
	cout << s1 << endl;
	return 0;
}