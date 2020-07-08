#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <memory>

using namespace std;

class TreeNode {
	friend class BinStrTree;
public:
	TreeNode()
		:value(string()), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(const string &val)
		:value(val), count(new int(1)), left(nullptr), right(nullptr) {}
	TreeNode(const TreeNode &tre)
		:value(tre.value),count(tre.count),left(tre.left),right(tre.right){} {
		++*count;
	}
	TreeNode& operator=(const TreeNode &rhs) {
		++*rhs.count;
		if (--*count == 0) {
			if (left) {
				delete left;
				left = nullptr;
			}
			if (right) {
				delete right;
				right = nullptr;
			}
			delete count;
		}
		value = rhs.value;
		count = rhs.count;
		left = rhs.left;
		right = rhs.right;
		return *this;
	}
	~TreeNode() {
		if (--*count == 0) {
			if (left) {
				delete left;
				left = nullptr;
			}
			if (right) {
				delete right;
				right = nullptr;
			}
			delete count;
			count = nullptr;
		}
	}
private:
	string value;
	int* count;
	TreeNode *left;
	TreeNode *right;
};

class BinStrTree {
public:
	BinStrTree():root(new TreeNode()){}
	BinStrTree(const BinStrTree &bin) :root(new TreeNode(*bin.root)){}
	BinStrTree & operator=(const BinStrTree&rhs) {
		auto p = new TreeNode(*rhs.root);
		delete root;
		root = p;
		return *this;
	}
	~BinStrTree() { delete root; }
private:
	TreeNode *root;
};

int main() {

	return 0;
}