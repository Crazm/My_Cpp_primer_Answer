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
	String():
		elements(nullptr), first_free(nullptr), cap(nullptr) {}
	String(const char *s) {
		auto newdata = alloc_n_copy(s, s + strlen(s));
		elements = newdata.first;
		first_free = cap = newdata.second;
		alloc.construct(first_free, 0);	//�ַ�������һ��Ϊ0
	}
	String(const String&s) {
		//����alloc_n_copy����ռ���������s��һ�����Ԫ��
		auto newdata = alloc_n_copy(s.begin(), s.end());
		elements = newdata.first;
		first_free = cap = newdata.second;
		alloc.construct(first_free, 0);	//�ַ�������һ��Ϊ0
	}
	String& operator=(String& rhs) {
		//����alloc_n_copy����ռ���������rhs��һ�����Ԫ��
		auto data = alloc_n_copy(rhs.begin(), rhs.end());
		free();
		elements = data.first;
		first_free = cap = data.second;
		alloc.construct(first_free, 0);	//�ַ�������һ��Ϊ0
		return *this;
	}
	String& operator=(const char *s) {
		//����alloc_n_copy����ռ���������rhs��һ�����Ԫ��
		auto data = alloc_n_copy(s, s+strlen(s));
		free();
		elements = data.first;
		first_free = cap = data.second;
		alloc.construct(first_free, 0);	//�ַ�������һ��Ϊ0
		return *this;
	}
	~String() {
		free();
	}
	void push_back(const char &s) {
		if (size() == capacity())	//ȷ���пռ�������Ԫ��
			reallocate();
		alloc.construct(first_free++, s);	//��first_freeָ���Ԫ���й���s�ĸ���
		alloc.construct(first_free, 0);	//�ַ�������һ��Ϊ0
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
		auto data = alloc.allocate(e - b + 1);	//����ռ䱣�������Χ��Ԫ��
		//��ʼ��������һ������Ԫ��֮���λ��
		return{ data,uninitialized_copy(b,e,data) };
	}
	void free() {
		if (elements) {
			//�������پ�Ԫ��
			for_each(elements, first_free+1, [this](char &p) { this->alloc.destroy(&p); });
			alloc.deallocate(elements, cap - elements+1);
		}
	}
	void reallocate() {
		//���ǽ����䵱ǰ������С���ڴ�ռ�
		auto newcapacity = size() ? 2 * size() : 1;
		//�������ڴ�
		auto newdata = alloc.allocate(newcapacity+1);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//�����õ����ƶ����캯��
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + newcapacity;
	}

};

int main() {
	String str1("hello,world!");
	String str2("sgf");
	String str3(str1);
	String str4 = "wugeuighqiwihiqhwe";
	str1.print();
	str2.print();
	str3.print();
	str4.print();
	str1.push_back('*');
	str1.print();
	return 0;
}