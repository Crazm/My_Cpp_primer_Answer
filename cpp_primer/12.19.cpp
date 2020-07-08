#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class StrBlob {
	friend class StrBlobPtr;
public:
	typedef vector<string>::size_type size_type;
	StrBlob() : data(make_shared<vector<string>>()) {}
	StrBlob(initializer_list<string> il) :
		data(make_shared<vector<string>>(il)) {}
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string &t)const { data->push_back(t); }
	void pop_back()const {
		check(0, "pop_back on empty StrBlob");
		data->pop_back();
	}
	StrBlobPtr begin();
	StrBlobPtr end();
	string & front()const {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	string & back()const {
		check(0, "back on empty StrBlob");
		return data->back();
	}

private:
	shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const {
		if (i >= data->size())
			throw out_of_range(msg);
	}
};

class StrBlobPtr {
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr( StrBlob &a, size_t sz = 0) :
		wptr(a.data), curr(sz) {}
	string& deref() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	StrBlobPtr& incr() {
		check(curr, "increasement past end of StrBlobPtr");
		++curr;
		return *this;
	}
	size_t get_curr() {
		return curr;
	}
private:
	shared_ptr<vector<string>>
		check(size_t i, const string &msg) const {
		auto ret = wptr.lock();
		if (!ret)
			throw runtime_error("unbound StrBlobPtr");
		if (i >= ret->size())
			throw out_of_range(msg);
		return ret;
	}
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

StrBlobPtr StrBlob::begin(){ return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

int main() {
	ifstream in("string.txt");
	StrBlob sb;
	string temp;
	while (in >> temp) {
		sb.push_back(temp);
	}
	StrBlobPtr begin = sb.begin();
	StrBlobPtr end = sb.end();
	while (begin.get_curr() < end.get_curr()) {
		cout << begin.deref() << " ";
		begin.incr();
	}
	return 0;
}