#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct stru {
	string str;
	int max;
};

int main()
{
	vector<string> str;
	string temp;
	stru save;
	save.max = 0;
	int i=0, j, cnt, n;
	while (cin >> temp) {
		str.push_back(temp);
	}
	n = str.size();
	for (i = 0; i < n; ++i) {
		for (j = i + 1, cnt = 1; j < n && str[j] == str[i]; ++j)
				cnt++;
		if (cnt != 1 && cnt >save.max) {
			save.str = str[i];
			save.max = cnt;
			i = j;
		}
		
	}
	if (save.max != 0)
		cout << save.str << " have appear : " << save.max << endl;
	else
		cout << "has no repetition" << endl;
	return 0;
}

//how now now now brown cow cow