#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main() {
	default_random_engine e(time(0));	//设置种子为时间
	uniform_int_distribution<unsigned> u(1, 9);		//设置均匀分布，范围为1:9
	for (int i = 0; i < 10; ++i) {
		cout << u(e) << " ";
	}
	cout << endl;
	return 0;
}