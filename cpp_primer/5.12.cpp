#include <iostream>
using namespace std;

int main()
{
	int ff_cnt = 0, fl_cnt = 0, fi_cnt = 0;
	char c;
	while (cin >> c) {
		switch (c) {
		case 'f':
		{
			cin >> c;
			switch (c)
			{
			case 'f':
				ff_cnt++;
				break;
			case 'l':
				fl_cnt++;
				break;
			case 'i':
				fi_cnt++;
				break;
			}
			break;
		}
		default:
			break;
		}
	}
	cout << ff_cnt << " " << fl_cnt << " " << fi_cnt << endl;
	return 0;
}