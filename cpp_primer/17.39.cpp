#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	//以读写的方式打开，并定位到文件末尾
	fstream inOut("fstest.txt", fstream::ate | fstream::in | fstream::out);
	if (!inOut)
	{
		cout << "打开文件失败" << endl;
		return EXIT_FAILURE;
	}
	auto end_mark = inOut.tellg();	//记录原文件的尾位置
	inOut.seekg(0, fstream::beg);	//再定位到文件开头
	size_t cnt = 0;			//字节数累加器
	string line;			//保存输入中的每一行
	while (inOut && inOut.tellg() != end_mark && getline(inOut, line)) {
		cnt += line.size() + 1;	//加一表示换行符
		auto mark = inOut.tellg();	//记录读取位置
		inOut.seekp(0, fstream::end);//将写标记定位到文件尾
		inOut << cnt;
		if (mark != end_mark)
			inOut << " ";
		inOut.seekg(mark);	//恢复读位置；
	}
	inOut.seekp(0, fstream::end);//将写标记定位到文件尾
	inOut << "\n";
	return 0;
}