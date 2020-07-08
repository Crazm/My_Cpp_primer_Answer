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
	//foleders����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const string &str = "") :	//Ĭ�Ϲ��캯��
		contents(str) {}
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message &m) :
		contents(m.contents), folders(m.folders) {
		add_to_Folders(m);//������Ϣ��ӵ�ָ��m��Folder��
	}
	Message& operator=(const Message &m) {
		//ͨ����ɾ��ָ���ٲ��������������Ը�ֵ���
		remove_from_Folders();	//��������Folder
		contents = m.contents;	//��m������Ϣ����
		folders = m.folders;	//��m����Folderָ��
		add_to_Folders(m);		//����message��ӵ���ЩFolder��
		return *this;
	}
	~Message() {
		remove_from_Folders();
	}
	void swap(Message &lhs, Message &rhs) {
		using std::swap;
		//��ÿ����Ϣ��ָ�����(ԭ��)���ڵ�Folder��ɾ��
		for (auto f : lhs.folders)
			f->remMsg(&lhs);
		for (auto f : rhs.folders)
			f->remMsg(&rhs);
		//����contents �� Folder ָ��set
		swap(lhs.folders, rhs.folders);
		swap(lhs.contents, rhs.contents);
		//��ÿ��Message��ָ����ӵ�����(�µ�)Folder��
		for (auto f : lhs.folders)
			f->addMsg(&lhs);
		for (auto f : rhs.folders)
			f->addMsg(&rhs);
	}
	//�Ӹ�����Folder���������/ɾ����Message
	void save(Folder &f) {
		folders.insert(&f);
		f.addMsg(this);
	}
	void remove(Folder &f) {
		folders.erase(&f);
		f.remMsg(this);
	}
	void addfod(Folder *f) {	//ע�ⲻ�ܼ�const
		folders.insert(f);
	}
	void remfod(Folder *f) {	//ע�ⲻ�ܼ�const
		folders.erase(f);
	}
	void print()
	{
		std::cout << contents << std::endl;
	}
private:
	string contents;	//ʵ����Ϣ����
	set<Folder*> folders;	//������Message��Folder
							//�������캯����������ֵ���㷨������������ʹ�õĹ��ߺ���
							//����Message��ӵ�ָ�������Folder
	void add_to_Folders(const Message &m) {
		for (auto f : m.folders)	//��ÿ������m��Folder
			f->addMsg(this);		//���Folder���һ��ָ��Message��ָ��
	}
	//��folders�е�ÿ��Folder��ɾ��Message
	void remove_from_Folders() {
		for (auto f : folders)		//��ÿ������m��Folder
			f->remMsg(this);		//��Folderɾ����Message
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