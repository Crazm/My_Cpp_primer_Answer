#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main() {
	default_random_engine e(time(0));	//��������Ϊʱ��
	uniform_int_distribution<unsigned> u(1, 9);		//���þ��ȷֲ�����ΧΪ1:9
	for (int i = 0; i < 10; ++i) {
		cout << u(e) << " ";
	}
	cout << endl;
	return 0;
}