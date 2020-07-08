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
	//构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob中元素的数目
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//添加和删除元素
	void push_back(const T &t) { data->push_back(t); }
	//移动版本
	void push_back(T &&t) { data->push_back(std::move(t));}
	void pop_back();
	//元素访问 
	typename vector<T>::iterator begin() { return data->begin(); } //在用到模板里的嵌套类型时，需要加上typename 
	typename vector<T>::iterator end() { return data->end(); }	   //依赖受限名称不能作为类型看待，除非在它前面加一个关键字：typename
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
	//如果i太大，抛出异常，阻止访问一个不存在的元素
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
		return (*p)[curr];	//(*p)为本对象指向的vector
	}
	//前置运算符
	BlobPtr& operator++();
	BlobPtr& operator--();//当处于类模板作用域中，不用带<T>类型符号
private:
	//若检查成功，返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<T>>
		check(std::size_t,const std::string &) const;
	//保存一个weak_ptr，表示底层vector可能被销毁
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

