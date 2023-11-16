#include <iostream>

using namespace std;

class Queue {
public:
	Queue(int capacity=2) {
		this->capacity = capacity;
		this->arr = new float[this->capacity];
		rear = 0; front = 0;
	}
	void push(float data) {
		
		if ((this->rear + 1) %this->capacity == this->front) {
			
			float* temp = new float[this->capacity*2];
			if (front < rear||front==capacity-1) {
				copy(this->arr+(front + 1)%capacity, this->arr + rear+1, temp);
			}else {
				copy(this->arr + front+1, this->arr + capacity , temp);
				copy(this->arr, this->arr + front , temp + capacity - front - 1);
			}

			delete[] this->arr;
			this->arr = temp;
			front = capacity*2 - 1;
			rear = capacity  - 2;
			this->capacity *= 2;
			
		}
		this->rear++;
		arr[this->rear] = data;

		
	}
	void pop() {
		if (front == rear) {
			return;
		}
		this->front = (this->front + 1) % this->capacity;
	}
	void print() {
		int i = this -> front;
		while (i != rear) {
			i++;
			i %= this->capacity;
			cout << arr[i]<<' ';
			
		}
		cout << endl;
	}
private:
	int front,rear;
	int capacity;
	float* arr;


};
int main() {


	Queue q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	q.push(5);
	q.push(6);
	q.push(7);
	q.print();
}