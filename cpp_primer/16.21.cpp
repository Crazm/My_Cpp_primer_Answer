#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

//普通类的成员模板
class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr ):os(s){}
	//与任何函数模板相同，T的类型由编译器推断
	template <typename T> void operator()(T *p) const
	{
		os << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream &os;
};

