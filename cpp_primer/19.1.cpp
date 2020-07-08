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
		//����alloc_n_copy����ռ���������s��һ�����Ԫ��
		auto newdata = alloc_n_copy(s.begin(), s.end());
		free();
		elements = newdata.first;
		first_free = cap = newdata.second;
	}
	strvec& operator=(strvec& rhs) {
		//����alloc_n_copy����ռ���������rhs��һ�����Ԫ��
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
		chk_n_alloc();	//ȷ���пռ�������Ԫ��
		alloc.construct(first_free++, s);	//��first_freeָ���Ԫ���й���s�ĸ���
	}
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	string* begin()const { return elements; }
	string* end()const { return first_free; }
	void alloc_n_move(size_t num) {
		//�������ڴ�
		auto newdata = alloc.allocate(num);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//�����õ����ƶ����캯��
		free();
		elements = newdata;
		first_free = dest;
		cap = elements + num;
	}
	void reserve(size_t num) {	//�ı�������С
		if (num < capacity()) return;	//����޸ĺ�����С��֮ǰ�ģ��򱣳�֮ǰ��������С
		alloc_n_move(num);
	}
	void resize(size_t count) {		//�ı�Ԫ����Ŀ
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
		auto data = alloc.allocate(e - b);	//����ռ䱣�������Χ��Ԫ��
											//��ʼ��������һ������Ԫ��֮���λ��
		return{ data,uninitialized_copy(b,e,data) };
	}
	void free() {
		//���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲôҲ����
		if (elements) {
			//�������پ�Ԫ��
			for (auto p = first_free; p != elements; )
				alloc.destroy(--p);
			alloc.deallocate(elements, cap - elements);
		}
	}
	void reallocate() {
		//���ǽ����䵱ǰ������С���ڴ�ռ�
		auto newcapacity = size() ? 2 * size() : 1;
		//�������ڴ�
		auto newdata = alloc.allocate(newcapacity);
		auto dest = newdata;
		auto elem = elements;
		for (auto i = 0; i != size(); ++i)
			alloc.construct(dest++, std::move(*elem++));	//�����õ����ƶ����캯��
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