#include <iostream>
#include <vector>
#include <string>
using namespace std;



int main()
{
	vector<int > num1,num2;
	int i , cnt, temp, n;
	cin >> n;
	while (cin >> temp && n--) 
		num1.push_back(temp);
	cin >> n;
	while (cin >> temp && n--)
		num2.push_back(temp);
	n = num1.size() < num1.size() ? num1.size() : num2.size();

	for (i = 0, cnt = 0; i < n; ++i)
		if (num1[i] == num2[i])
			++cnt;
	if (cnt == i)
		cout << "°üº¬\n" << endl;
	else
		cout << "²»°üº¬\n" << endl;
	return 0;
}