#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <set>
#include <math.h>
using namespace std;
class Term {
	friend class Polynomial;
public:

	Term(float coef, int exp) {
		this->coef = coef;
		this->exp = exp;
	}
	Term() = default;
private:
	float coef;
	int exp;
};

class Polynomial {
public:
	Polynomial() {
		this->terms = new Term[2];
		this->capacity = 2;
		this->max_degree = 0;
		this->size = 0;
	}
	Polynomial(vector <  pair<float, int>> vec) {
		this->terms = new Term[2];
		this->capacity = 2;
		this->max_degree = 0;
		this->size = 0;
		for (int i = 0; i < vec.size(); i++) {
			newItem(Term(vec[i].first, vec[i].second));
		}

	}
	//should be added sorted
	void newItem(const Term& term) {
		if (size == capacity) {
			this->capacity *= 2;
			Term* temp = new Term[capacity];
			copy(terms, terms + size, temp);

			delete[] this->terms;
			this->terms = temp;
		}
		this->terms[size] = term;
		size++;
	}
	Polynomial Add(const Polynomial& pol2)
	{
		Polynomial result;
		int a_pos = 0; int b_pos = 0;
		while (a_pos < this->size && b_pos < pol2.size) {
			if (this->terms[a_pos].exp ==pol2.terms[b_pos].exp) {
				float add_result = this->terms[a_pos].coef + pol2.terms[b_pos].coef;
				if (add_result)result.newItem({ add_result ,this->terms[a_pos].exp });
				a_pos++;
				b_pos++;
			}
			else if (this->terms[a_pos].exp > pol2.terms[b_pos].exp) {
				result.newItem({ this->terms[a_pos].coef ,this->terms[a_pos].exp });
				a_pos++;

			}
			else {
				result.newItem({ pol2.terms[b_pos].coef ,pol2.terms[b_pos].exp });
				b_pos++;

			}
		}
		for (; a_pos < this->size; a_pos++) {
			result.newItem({ this->terms[a_pos].coef,this->terms[a_pos].exp });
		}
		for (; b_pos < this->size; b_pos++) {
			result.newItem({ pol2.terms[b_pos].coef,pol2.terms[b_pos].exp });
		}
		return result;


	}
	Polynomial operator+(const Polynomial& pol2) {
		return Add(pol2);
	}
	void print() {
		for (int i = 0; i < size; i++) {
			if (this->terms->coef < 0)
				cout << this->terms->coef << "x^" << this->terms[i].exp;
			else
				cout << '+' << this->terms[i].coef << "x^" << this->terms[i].exp;



		}
		cout << endl;
	}
private:
	int capacity;
	int max_degree;
	int size;
	Term* terms;

};
int main() {

	Polynomial pol1({ {2, 5}, { 2,3 }, { 5,1 }, { 3,0 } });
	Polynomial pol2({ {1, 5}, { 2,2 }, { 4,1 }, { 3,0 } });
	pol1.print();
	pol2.print();
	(pol1 + pol2).print();



}