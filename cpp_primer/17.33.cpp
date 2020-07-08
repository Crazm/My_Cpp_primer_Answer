#include <iostream>
#include <random>
#include <time.h>

using namespace std;

int main() {
	default_random_engine e;
	bernoulli_distribution b;
	for (int i = 0; i < 10; ++i) {
		if (b(e))
			cout << "Hello!" << endl;
		else
			cout << "world!" << endl;
	}
	return 0;
}