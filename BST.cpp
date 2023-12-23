#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include<utility>
using namespace std;


template <typename T>
class BST;

long long int composition(int k, int n) {
	//can be done in one loop but the precision might not be accurate
	long long int up = 1;
	long long int down = 1;
	for (int i = n - k + 1; i <= n; i++)
		up *= i;
	for (int i = 1; i <= k; i++) {
		down *= i;
	}
	return up / down;
}

template<typename T>
class Node {
	friend class BST<T>;
public :
	Node() = default;
	Node(T data,Node<T>* parent=nullptr,Node* left=nullptr,Node* right=nullptr) {
		this->parent = parent;
		this->data = data;
	
		this->right = right;
		this->left = left;
	}
	T getData() { return this->data; }

private:
	Node* right;
	Node* left;
	Node* parent;
	T data;
	
};

template<typename T>
class BST {
public:
	BST(T root_data) {
		root = new Node<T>(root_data);

	}
	BST() {
		root = nullptr;
	}
	BST(const vector<T>& sequence) {
		for (const auto& i : sequence) {
			this->push(i);

		}
	}
	void push(T data) {
		if (!root) {
			root = new Node<T>(data);
			return;
		}
		Node<T>* temp = root;
		while (true) {
			if (data >= temp->data) {
				if (temp->right ) {
					temp = temp->right;
				}
				else {
					temp->right = new Node<T>(data,temp);
					break;
				}
			}
			else {
				if (temp->left) {
					temp = temp->left;
				}
				else {
					temp->left = new Node<T>(data, temp);
					break;
				}

			}
		}

	}
	void BFSPrint() {
		int nodes_in_same_height=1;
		int nodes_in_next_same_height=0;
		queue<Node<T>*> nodes;
		Node<T>* prev_parent = nullptr;
		if (root != nullptr)
			nodes.push(root);
		while (!nodes.empty()) {
			Node<T>* node = nodes.front();
			nodes.pop();
			
			if (node->left) {
				nodes.push(node->left);
				nodes_in_next_same_height++;
			}
			if (node->right ) {
				nodes.push(node->right);
				nodes_in_next_same_height++;
			}
			if (prev_parent != node->parent) {

				
				cout  <<"   " <<node->parent->data << ": ";
				prev_parent = node->parent;
			}
			cout << node->data << ' ';
			nodes_in_same_height--;
			if (!nodes_in_same_height) {
				
				nodes_in_same_height = nodes_in_next_same_height;
				nodes_in_next_same_height = 0;
				prev_parent = node->parent;
				cout << endl;
			}
		}

	}
	Node<T>* getByString(string rl) {
		if (rl.empty())
			return root;
		if (!root)
			throw "out of range";

		int index = 0;
		Node<T>* temp = root;
		while (index != rl.size()) {
			if (rl[index] == 'r') {
				if (!(temp-> right))
					throw "out of range";
				temp = temp->right;
			}
			if (rl[index] == 'l') {
				if (!(temp-> left))
					throw "out of range";
				temp = temp->left;
			}
			index++;


		}
		return temp;
	}
	void Delete(Node<T>* node) {
		
		if (!node->right)
			transplant(node, node->left);
		else if(!node->left)
			transplant(node, node->right);
		else {
			//finding tree minimum;
			Node<T>* temp = node;
			while (temp->left) {
				temp = temp->left;
			}
			//temp is tree minimum
			if (temp->parent != node) {
				transplant(temp, temp->right);
				temp->right = node->right;
				temp->right->parent = temp;
			}
			transplant(node, temp);
			temp->left = node->left;
			temp->left->parent = temp;
		}

	}
	void DeleteByString(string s) {
		this->Delete(getByString(s));
	}



	
private:
	void transplant(Node<T>* original, Node<T>* replacement) {
		if (!original->parent)
			this->root = replacement;
		else if (original == original->parent->right)
			original->parent->right = replacement;
		else
			original->parent->left = replacement;
		if (replacement)
			replacement->parent = original->parent;

	}
	Node<T>* root;

};

int main() {
	

}