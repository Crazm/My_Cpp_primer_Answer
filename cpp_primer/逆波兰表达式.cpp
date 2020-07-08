#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

string transfer(string input) {
	stack<char> sta;
	string output;
	for (unsigned i = 0; i < input.size(); ++i) {
		while (isdigit(input[i]))
		{
			output.push_back(input[i]);
			++i;
			if (!isdigit(input[i])) {
				output.push_back(' ');
				break;
			}
		}
		if (input[i] == ')') {
			char c;
			c = sta.top();
			sta.pop();
			while (c != '(')
			{
				output.push_back(c);
				output.push_back(' ');
				c = sta.top();
				sta.pop();
			}
		}
		else if (input[i] == '+' || input[i] == '-') {
			if (sta.empty())
				sta.push(input[i]);
			else {
				char c;
				do {
					c = sta.top();
					sta.pop();
					if (c == '(')
						sta.push(c);
					else {
						output.push_back(c);
						output.push_back(' ');
					}
				} while (!sta.empty() && c != '(');
				sta.push(input[i]);
			}
		}
		else if (input[i] == '*' || input[i] == '/' || input[i] == '(')
			sta.push(input[i]);
	}
	while (!sta.empty()) {
		char c = sta.top();
		sta.pop();
		output.push_back(c);
		output.push_back(' ');
	}
	return output;
}

double Process(string input) {
	stack<double> result;
	string num;
	double a, b;
	for (unsigned i = 0; i < input.size(); ++i) {
		while (isdigit(input[i]))
		{
			num.push_back(input[i]);
			++i;
			if (!isdigit(input[i])) {
				result.push(stod(num));
				num.clear();
				break;
			}
		}
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' ) {
			a = result.top();
			result.pop();
			b = result.top();
			result.pop();
			switch (input[i]) {
			case '+':
				result.push(b + a);
				break;
			case '-':
				result.push(b - a);
				break;
			case '*':
				result.push(b * a);
				break;
			case '/':
				if (a != 0)
					result.push(b / a);
				else
					return INFINITY;
				break;
			}
		}
	}
	return result.top();
}

int main() {
	string input;
	cin >> input;
	double result = Process(transfer(input));
	cout << result << endl;
	return 0;
}