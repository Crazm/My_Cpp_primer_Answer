#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include <set>
#include <map>

using namespace std;

class String {
public:
	String() :
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	String(const char *s) {
		auto newdata = alloc_n_copy(s, s + strlen(s));
		elements = newdata.first;
		first_free = cap = newdata.second;
		alloc.construct(first_free, 0);	//字符串后面一个为0
		cout << "String(const char *s)" << endl;
	}
	String(const String&s) {
		//调用alloc_n_copy分配空间以容纳与s中一样多的元素
		auto newdata = alloc_n_copy(s.begin(), s.end());
		elements = newdata.first;
		first_free = cap = newdata.second;
		alloc.construct(first_free, 0);	//字符串后面一个为0
		cout << "String(const String&s)" << endl;
	}
	String(String &&s) noexcept:
	elements(s.elements), first_free(s.first_free),cap(s.cap){
		s.elements = s.first_free = s.cap = nullptr;
		cout << "String(String &&s)" << endl;
	}
	String& operator=(String&& rhs)noexcept {
		if (this != &rhs) {
			alloc = std::move(rhs.alloc);
			elements = rhs.elements;
			first_free = rhs.first_free;
			cap = rhs.cap;
			rhs.elements = rhs.first_free = rhs.cap = nullptr;
		}
		cout << "String& operator=(String&& rhs)" << endl;
		return *this;
	}
	String& operator=(String& rhs) {
		//调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
		alloc.construct(first_free, 0);	//字符串后面一个为0
		cout << "String& operator=(String& rhs)" << endl;
		return *this;
	}
	String& operator=(const char *s) {
		//调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
		auto data = alloc_n_copy(s, s + strlen(s));
		free();
		elements = data.first;
		first_free = cap = data.second;
		alloc.construct(first_free, 0);	//字符串后面一个为0
		return *this;
	}
	~String() {
		free();
	}
	void push_back(const char &s) {
		if (size() == capacity())	//确保有空间容纳新元素
			reallocate();
		alloc.construct(first_free++, s);	//在first_free指向的元素中构造s的副本
		alloc.construct(first_free, 0);	//字符串后面一个为0
	}
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	char* begin()const { return elements; }
	char* end()const { return first_free; }
	void print() {
		cout << elements << endl;
	}
private:
	allocator<char> alloc;
	char *elements;
	char *first_free;
	char *cap;
	pair<char*, char*> alloc_n_copy(const char* b, const char* e) {
		auto data = alloc.allocate(e - b + 1);	//分配空间保存给定范围的元素
												//初始化并返回一个构造元素之后的位置
		return{ data,uninitialized_copy(b,e,data) };
	}
	void free() {
		if (elements) {
			//逆序销毁旧元素
			for_each(elements, first_free + 1, [this](char &p) { this->alloc.destroy(&p); });
			alloc.deallocate(elements, cap - elements + 1);
		}
	}
	void reallocate() {
		//我们将分配当前两倍大小的内存空间
		auto newcapacity = size() ? 2 * size() : 1;
		//分配新内存
		auto newdata = alloc.allocate(newcapacity + 1);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//这里用到了移动构造函数
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}
};

int main() {
	String s1("hello");
	String s2 = s1;
	String s3 = std::move(s1);
	s2.print();
	return 0;
}