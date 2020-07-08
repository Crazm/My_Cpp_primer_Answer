#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <memory>

using namespace std;

//��ͨ��ĳ�Աģ��
class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr ):os(s){}
	//���κκ���ģ����ͬ��T�������ɱ������ƶ�
	template <typename T> void operator()(T *p) const
	{
		os << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream &os;
};

