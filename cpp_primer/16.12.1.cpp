#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

template <typename T> class BlobPtr {
public:
	BlobPtr():curr(0){}
private:
	std::shared_ptr<std::vector<T>>
		check(std::size_t const std::string &) const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};