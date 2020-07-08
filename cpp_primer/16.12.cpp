#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template <typename T> class Blob {
public:
	typedef T value_type;
	typedef typename std::vector<T> ::size_type size_type;
	//���캯��
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob��Ԫ�ص���Ŀ
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//��Ӻ�ɾ��Ԫ��
	void push_back(const T &t) { data->push_back(t); }
	//�ƶ��汾
	void push_back(T &&t) { data->push_back(std::move(t));}
	void pop_back();
	//Ԫ�ط��� 
	typename vector<T>::iterator begin() { return data->begin(); } //���õ�ģ�����Ƕ������ʱ����Ҫ����typename 
	typename vector<T>::iterator end() { return data->end(); }	   //�����������Ʋ�����Ϊ���Ϳ�������������ǰ���һ���ؼ��֣�typename
	T& front();
	T& back();
	T& operator[](size_type i);
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::front() {
	check(0, "front on empty Blob");
	return data->front();
}

template <typename T>
T& Blob<T>::back() {
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i) {
	//���i̫���׳��쳣����ֹ����һ�������ڵ�Ԫ��
	check(i, "subscript out of range");
	return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back(){
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template <typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>()){}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
	data(std::make_shared<std::vector<T>>(il)) {}


template <typename T> class BlobPtr {
public:
	BlobPtr() :curr(0) {}
	BlobPtr(Blob<T> &a, size_t sz = 0):
		wptr(a.data),curr(sz){}
	T& operator*()const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];	//(*p)Ϊ������ָ���vector
	}
	//ǰ�������
	BlobPtr& operator++();
	BlobPtr& operator--();//��������ģ���������У����ô�<T>���ͷ���
private:
	//�����ɹ�������һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<T>>
		check(std::size_t,const std::string &) const;
	//����һ��weak_ptr����ʾ�ײ�vector���ܱ�����
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

template <typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t cur, const std::string &msg) const {
	if (cur >= wptr->size())
		throw std::out_of_range(msg);
	return wptr;
}


template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
	auto p = check(curr+1, "operator++ out of range");
	if (p)
		curr = curr +1;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	if (curr - 1 < 0)
		throw std::out_of_range("curr - 1 < 0");
	curr = curr - 1;;
	return *this;
}

int main() {
	Blob<int> bob = { 1,2,3,4,5 };
	for (auto i : bob)
		cout << i << endl;
	for (int i = 0; i != bob.size(); ++i)
		bob[i] = i*i;
	for (auto i : bob)
		cout << i << endl;
	return 0;
}

