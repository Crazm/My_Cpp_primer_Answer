#include <iostream>
using namespace std;

int main()
{
	int a_cnt = 0, e_cnt = 0,i_cnt = 0, o_cnt = 0, u_cnt = 0;
	char c;
	while (cin >> c) {
		switch (c) {
		case 'a':case 'A':
			++a_cnt;
			break;
		case 'e':case 'E':
			++e_cnt;
			break;
		case 'i':case 'I':
			++i_cnt;
			break;
		case 'o':case 'O':
			++o_cnt;
			break;
		case 'u':case 'U':
			++u_cnt;
			break;
		default:
			break;
		}
	}
	cout << a_cnt << " " << e_cnt << " " << i_cnt << " " << o_cnt << " " << u_cnt << endl;
	return 0;
}