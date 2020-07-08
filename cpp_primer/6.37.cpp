#include <iostream>
#include <vector>
#include <string>

using namespace std;

string make_plural(size_t ctr, const string &word,const string &ending = "s")
{
	return (ctr > 1) ? word + ending : word;
}

int main(int argc, char *argv[])
{
	cout << make_plural(1, "success") << endl;
	cout << make_plural(2, "success") << endl;
	return 0;
}