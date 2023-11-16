#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
class Exp {
public:
	void addExp(const string& exp) {
		expresions.push_back(exp);
	}
	void addExp(float exp) {
		expresions.push_back(to_string(exp));

	}
	void ConvertToPostfix() {
		Exp temp;
		stack<string> exp_stack;
		for (const auto& exp:expresions) {
			if (isOperator(exp)) {
				if (exp == ")") {
					while (exp_stack.top() != "(") {
						temp.addExp(exp_stack.top());
						exp_stack.pop();
					}
						exp_stack.pop();

				}
				else {
					if (!exp_stack.empty()) {
						while (!exp_stack.empty() && compare(exp[0], exp_stack.top()[0]) == 1) {
							string exp = exp_stack.top();
							temp.addExp(exp);
							exp_stack.pop();

						}
					}
					exp_stack.push(exp);
				}
			}
			else {
				temp.addExp(exp);
			}
			
		}
		while (!exp_stack.empty()) {
			temp.addExp(exp_stack.top());
			exp_stack.pop();
		}
		*this=temp;

	}
	float executeOperation(float n1, float n2, string op) {
		if (op == "^")
			return pow(n1, n2);
		else if (op == "*")
			return n1 * n2;
		else if (op == "/")
			return n1 / n2;
		else if (op == "+")
			return n1 + n2;
		else if (op == "-")
			return n1 - n2;
		
		
	}
	float eval() {
		stack<float> result;
		for (const auto& exp :expresions) {
			if (isOperator(exp)) {
				float op1 = result.top();
				result.pop();
				float op2 = result.top();
				result.pop();
				result.push(executeOperation(op2, op1, exp));
			}
			else {
				result.push(convertToNumber(exp));
			}
		}
		return result.top();
	}

	void print() {
		for (const auto& exp:expresions) {
			cout << exp<<' ';
		}
		cout << endl;
	}
	
private:
	vector<string> expresions;
	int index = 0;
	const char* operators = "-= */ ^";
	
	string next() { this->index++; return expresions[this->index]; }
	int reachedEnd() { return (this->index == expresions.size() - 1); }
	int refresh() { this->index = 0; }
	bool isOperator(string s) {
		if (s.size() > 1 || (s != "/" && s != "*" && s != "^" && s != "+" && s != "-" && s!="("&& s!=")")) {
			return false;
		}
		return true;
	}
	
	float convertToNumber(string s) {
		return stof(s.c_str());
	}
	int compare(char c1,char c2) {
		int index1 = -1, index2 = -1;
		for (int i = 0; i < strlen(operators); i++) {
			if (c1 == operators[i]) {
				index1 = i;
			}
			if (c2 ==operators[i])
				index2 = i;
		}
		if (index1 > index2 && abs(index1 - index2) != 1)
			return -1;
		else if (index2 > index1 && abs(index1 - index2) != 1)
			return 1;
		else
			return 0;


	}
};

int main()
{
	string s;
	string temp;
	getline(cin, s);
	Exp exps;
	for (const auto& c : s) {
		if (c == ' ') {
			exps.addExp(temp);
			temp.clear();
		}
		else {
			temp.push_back(c);

		}
	}
	exps.addExp(temp);
	temp.clear();
	exps.ConvertToPostfix();
	cout << exps.eval();


}
