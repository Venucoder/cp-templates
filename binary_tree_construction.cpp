#include<bits/stdc++.h>
using namespace std;

class Node {
public:
	int data;
	Node *left, *right;

	Node(int val): data(val), left(nullptr), right(nullptr) {}
};

Node* construct_tree(vector<int> &arr, int i, int n) {
	Node* root = nullptr;
	if(i < n && arr[i] != -1) {
		root = new Node(arr[i]);
		root->left = construct_tree(arr, 2*i+1, n);
		root->right = construct_tree(arr, 2*i+2, n);
	}
	return root;
}

void print_inorder(Node* root) {
	if(!root) return;

	print_inorder(root->left);
	cout << root->data << " ";
	print_inorder(root->right);
}

int main() {	
	vector<int> arr{1, 2, 3, -1, 4, -1, 5, -1, -1, 6, 7, -1, -1, 8, -1};	
	int n = arr.size();
	Node *root = construct_tree(arr, 0, n);
	print_inorder(root);
}
