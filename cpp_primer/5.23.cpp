#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	int a, b;
	while (cin >> a >> b)
	{
		try {
			if (b == 0)
				throw runtime_error("divisor isn't zero\n");
			else 
				cout << static_cast <double>(a)/ b << endl;
		}catch(runtime_error err) { 
			cout << err.what() << "Try again ? Enter y or n" << endl;
			char c;
			cin >> c;
			if (!cin || c == 'n')
				break;
		}
		
	}
	return 0;
}