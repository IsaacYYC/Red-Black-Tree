#include "RBNode.h"

RBNode::RBNode(int d) {
	data = d;
	black = false;
	left = null;
	right = null;
}
RBNode::~RBNode() {
	delete left;
	delete right;
}