#ifndef TEMPLATE_H
#define TEMPLATE_H

template<typename T>
int compare(const T &v1, const T &v2) {
	if (v1 < v2)
		return -1;
	if (v2 < v1)
		return 1;
	return 0;
}

template<typename T, typename U>
bool Find(const T &beg, const T &end, const U &v2) {
	for (auto i = beg; i != end; ++i)
		if (*i == v2)
			return true;
	return false;
}

template<typename T>
void print(const T &arr) {
	for (auto elem : arr)
		cout << elem << endl;
}

template<typename T,unsigned N >
T* begin(const T (&arr)[N]) {
	//引用数组是非法的, (&arr即可)
	return arr;
}

template<typename T, unsigned N >
T* end(const T (&arr)[N]) {
	return arr+N;
}

template<typename T, unsigned N >
constexpr size_t Size(const T (&arr)[N]) {
	return N;
}

#endif