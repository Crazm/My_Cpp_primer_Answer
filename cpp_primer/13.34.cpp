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

class Folder {
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder &f);
	Folder& operator=(const Folder &f);
	~Folder();
	void addMsg(Message *m) {
		Msg.insert(m);
	}
	void remMsg(Message *m) {
		Msg.erase(m);
	}
	void print();
private:
	set<Message*> Msg;
	void add_to_Messages(const Folder&f);
	void remove_from_Messages();
};

class Message {
	friend class Folder;
public:
	//foleders被隐式初始化为空集合
	explicit Message(const string &str = "") :	//默认构造函数
		contents(str) {}
	//拷贝控制成员，用来管理指向本Message的指针
	Message(const Message &m) :
		contents(m.contents), folders(m.folders) {
		add_to_Folders(m);//将本消息添加到指向m的Folder中
	}
	Message& operator=(const Message &m) {
		//通过先删除指针再插入它们来处理自赋值情况
		remove_from_Folders();	//更新已有Folder
		contents = m.contents;	//从m拷贝消息内容
		folders = m.folders;	//从m拷贝Folder指针
		add_to_Folders(m);		//将本message添加到那些Folder中
		return *this;
	}
	~Message() {
		remove_from_Folders();
	}
	void swap(Message &lhs, Message &rhs) {
		using std::swap;
		//将每个消息的指针从它(原来)所在的Folder中删除
		for (auto f : lhs.folders)
			f->remMsg(&lhs);
		for (auto f : rhs.folders)
			f->remMsg(&rhs);
		//交换contents 和 Folder 指针set
		swap(lhs.folders, rhs.folders);
		swap(lhs.contents, rhs.contents);
		//将每个Message的指针添加到它的(新的)Folder中
		for (auto f : lhs.folders)
			f->addMsg(&lhs);
		for (auto f : rhs.folders)
			f->addMsg(&rhs);
	}
	//从给定的Folder集合中添加/删除本Message
	void save(Folder &f) {
		folders.insert(&f);
		f.addMsg(this);
	}
	void remove(Folder &f) {
		folders.erase(&f);
		f.remMsg(this);
	}
	void addfod(Folder *f) {	//注意不能加const
		folders.insert(f);
	}
	void remfod(Folder *f) {	//注意不能加const
		folders.erase(f);
	}
	void print()
	{
		std::cout << contents << std::endl;
	}
private:
	string contents;	//实际消息内容
	set<Folder*> folders;	//包含本Message的Folder
							//拷贝构造函数，拷贝赋值运算法和析构函数所使用的工具函数
							//将本Message添加到指向参数的Folder
	void add_to_Folders(const Message &m) {
		for (auto f : m.folders)	//对每个包含m的Folder
			f->addMsg(this);		//向该Folder添加一个指向本Message的指针
	}
	//从folders中的每个Folder中删除Message
	void remove_from_Folders() {
		for (auto f : folders)		//对每个包含m的Folder
			f->remMsg(this);		//从Folder删除本Message
	}
};


Folder::Folder(const Folder &f) :Msg(f.Msg) {
	add_to_Messages(f);
}
Folder& Folder::operator=(const Folder &f) {
	remove_from_Messages();
	Msg = f.Msg;
	add_to_Messages(f);
	return *this;
}
Folder::~Folder() {
	remove_from_Messages();
}

void Folder::print() {
	for (auto m : Msg)
		cout << m->contents << " ";
	cout << endl;
}

void Folder::add_to_Messages(const Folder&f) {
	for (auto i : f.Msg)
		i->folders.insert(this);
}
void Folder::remove_from_Messages() {
	for (auto i : Msg)
		i->folders.erase(this);
}


int main() {

	return 0;
}