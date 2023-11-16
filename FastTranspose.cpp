#include <iostream>
#include <stack>
#include <vector>
#include <utility>
#include <set>
#include <math.h>
using namespace std;
class Term {
	friend class SparseMatrix;
public:

	Term(int row, int column, float value) {
		this->row = row;
		this->column = column;
		this->value = value;
	}
	Term() {};
	void transpose() {
		float temp = this->row;
		this->row = this->column;
		this->column = temp;

	}
private:
	int row;
	int column;
	float value;
};

class SparseMatrix {
public:
	SparseMatrix(int rows, int columns, int capacity = 2) {
		this->size = 0;
		this->capacity = capacity;
		terms = new Term[capacity];
		this->rows = rows;
		this->cols = columns;

	}
	void transpose() {
		int max_row = -1;
		for (int i = 0; i < this->size; i++) {
			this->terms[i].transpose();
			if (this->terms[i].row > max_row)
				max_row = this->terms[i].row;
		}


		int* counter = new int[max_row + 1] ;
		for (int i = 0; i < max_row + 1; i++) {
			counter[i] = 0;
		}

		for (int i = 0; i < this->size; i++) {
			counter[this->terms[i].row]++;
			
		}
		int cnt = 0;
		for (int i = 0; i < max_row+1; i++) {
			cnt += counter[i];
			counter[i] = cnt;
		}

		Term* temp = new Term[this->capacity];
		for (int i = this->size - 1; i >= 0; i--) {
			temp[counter[this->terms[i].row] -1] = this->terms[i];
			counter[this->terms[i].row]--;
		}
		delete[] terms;
		this->terms = temp;




	}
	void newItem( Term term) {
		if (term.value == 0)
			return;
		if (this->capacity == this->size) {
			this->capacity *= 2;
			Term* temp = new Term[this->capacity];
			for (int i = 0; i < this->size; i++) {
				temp[i] = terms[i];
			}
			delete[] terms;
			this->terms = temp;
		}
		this->terms[size] = term;
		this->size++;

	}
	void print() {
		
		int pos = 0;
		for (int i = 0; i < this->rows; i++) {
			for (int j = 0; j < this->cols; j++) {
				if (pos < this->size && this->terms[pos].row == i && this->terms[pos].column == j) {
					cout << this->terms[pos].value << ' ';
					pos++;
				}
				else {
					cout << 0 << ' ';
				}


			}
			cout << endl;
		}
		cout << endl;
	}
private:
	int capacity;
	int size;
	Term* terms;
	int rows;
	int cols;
};
int main() {
	int n, m;
	cin >> n >> m;

	SparseMatrix matrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			float temp;
			cin >> temp;
			matrix.newItem({ i,j,temp });
		}
	}
	matrix.transpose();
	matrix.print();

}