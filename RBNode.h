#pragma once

class RBNode {
public:
	RBNode(int d);
	~RBNode();
private:
	int data;
	bool black;
	RBNode* left;
	RBNode* right;
};