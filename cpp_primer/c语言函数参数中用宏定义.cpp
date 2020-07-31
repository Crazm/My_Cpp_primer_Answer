#include <stdio.h>
#define MA(x,y) ((x)+(y))

int sum(int a, int b) {
	return a + b;
}

int main() {
	int a = 1;
	int & const b = a;
	const int &c = 111;
	b = 9;
	printf("%d\n", sum(e, MA(2,3)));
	return 0;
}