#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>
#include <set>
using namespace std;

void* operator new (size_t size){
	if (void * res = malloc(size))
		return res;
	else
		throw bad_alloc();
}

void operator delete (void *mem) {
	free(mem);
}

class strvec {
public:
	strvec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	strvec(initializer_list<string> strs) {
		auto newdata = alloc_n_copy(strs.begin(), strs.end());
		elements = newdata.first;
		first_free = cap = newdata.second;
	}
	strvec(const strvec&s) {
		//调用alloc_n_copy分配空间以容纳与s中一样多的元素
		auto newdata = alloc_n_copy(s.begin(), s.end());
		free();
		elements = newdata.first;
		first_free = cap = newdata.second;
	}
	strvec& operator=(strvec& rhs) {
		//调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
		return *this;
	}
	~strvec() {
		free();
	}
	void push_back(const string &s) {
		chk_n_alloc();	//确保有空间容纳新元素
		alloc.construct(first_free++, s);	//在first_free指向的元素中构造s的副本
	}
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin()const { return elements; }
	string* end()const { return first_free; }
	void alloc_n_move(size_t num) {
		//分配新内存
		auto newdata = alloc.allocate(num);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//这里用到了移动构造函数
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + num;
	}
	void reserve(size_t num) {	//改变容量大小
		if (num < capacity()) return;	//如果修改后容量小于之前的，则保持之前的容量大小
		alloc_n_move(num);
	}
	void resize(size_t count) {		//改变元素数目
		if (count > capacity()) return;
		alloc_n_move(count);
	}
private:
	static allocator<string> alloc;
	void chk_n_alloc() {
		if (size() == capacity())
			reallocate();
	}
	pair<string*, string*> alloc_n_copy(const string* b, const string* e) {
		auto data = alloc.allocate(e - b);	//分配空间保存给定范围的元素
											//初始化并返回一个构造元素之后的位置
		return{ data,uninitialized_copy(b,e,data) };
	}
	void free() {
		//不能传递给deallocate一个空指针，如果elements为0，则函数什么也不做
		if (elements) {
			//逆序销毁旧元素
			for (auto p = first_free; p != elements; )
				alloc.destroy(--p);
			alloc.deallocate(elements, cap - elements);
		}
	}
	void reallocate() {
		//我们将分配当前两倍大小的内存空间
		auto newcapacity = size() ? 2 * size() : 1;
		//分配新内存
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//这里用到了移动构造函数
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}
	string *elements;
	string *first_free;
	string *cap;
};


int main() {
	strvec str;
	str.push_back("sgf");
	cout << *(str.begin()) << endl;
	return 0;
}