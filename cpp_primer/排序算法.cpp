#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<int> &vec) {
	for (int i = 0, temp; i != vec.size()-1; ++i)
		for (int j = vec.size() - 1; j > i; --j)
			if (vec[j - 1] > vec[j]) {
				temp = vec[j];
				vec[j] = vec[j - 1];
				vec[j - 1] = temp;
			}
}

void selection_sort(vector<int> &vec) {
	for (int i = 0, temp; i != vec.size(); ++i) {
		int min = i;
		for (int j = i + 1; j != vec.size(); ++j)
			if (vec[min] > vec[j])
				min = j;
		if (min != i) {
			temp = vec[i];
			vec[i] = vec[min];
			vec[min] = temp;
		}
	}
}
void insert_sort(vector<int> &vec) {

}

int main() {
	vector<int> vec{ 0,2,4,7,1,8,9,5,3,6 };
	selection_sort(vec);
	for (auto i : vec)
		cout << i << ' ';
	return 0;
}