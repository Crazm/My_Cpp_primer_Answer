#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class StrBlob{
public:
	typedef vector<string>::size_type size_type;
	StrBlob():data(make_shared<vector<string>>()){}
	StrBlob(initializer_list<string> il) :
		data(make_shared<vector<string>> (il)){}
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const string &t)const { data->push_back(t); }
	void pop_back()const { 
		check(0, "pop_back on empty StrBlob");
		data->pop_back(); 
	}
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

int main() {
	StrBlob b1;
	{
		StrBlob b2 = { "a","an","the" };
		b1 = b2;
		b2.push_back("about");
	}
	b1;
	return 0;
}