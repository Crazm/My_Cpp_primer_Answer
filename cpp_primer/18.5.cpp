#include <iostream>

using namespace std;

int main() {
	try {

	}
	catch (overflow_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (underflow_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (range_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (domain_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (invalid_argument &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (out_of_range &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (length_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (runtime_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (logic_error &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (bad_cast &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (bad_alloc &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	catch (exception &eobj) {
		cout << eobj.what() << endl;
		abort();
	}
	return 0;
}