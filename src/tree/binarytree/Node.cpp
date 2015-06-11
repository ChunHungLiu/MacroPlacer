#include "tree/binarytree/Node.h"
#include "tree/binarytree/NextNodesBehavior.h"
#include "tree/binarytree/NextNodesBehaviorLeftFirst.h"

Node::Node() {
    parentNode = 0;
    leftNode = 0;
    rightNode = 0;
    nextNodesBehavior = new NextNodesBehaviorLeftFirst();
}

Node::~Node() {
    delete nextNodesBehavior;
}

void Node::_setId(int id) {
    this->id = id;
}

int Node::_getId() {
    return id;
}

void Node::setParentNode(Node *node) {
    parentNode = node;
}

Node *Node::getParentNode() {
    return parentNode;
}

void Node::setLeftNode(Node *node) {
    leftNode = node;
}

Node *Node::getLeftNode() {
    return leftNode;
}

void Node::setRightNode(Node *node) {
    rightNode = node;
}

Node *Node::getRightNode() {
    return rightNode;
}

bool Node::isLeftNode() {
    // If the Node has no parent, an error occurs.
    return parentNode->getLeftNode() == this;
}

bool Node::hasLeftNode() {
    return leftNode != 0;
}

bool Node::hasRightNode() {
    return rightNode != 0;
}

Node *Node::copy() {
    Node *node = new Node();
    node->setParentNode(parentNode);
    node->setLeftNode(leftNode);
    node->setRightNode(rightNode);
    node->_setId(id);
    node->setNextNodesBehavior(nextNodesBehavior->copy());
    return node;
}

void Node::setNextNodesBehavior(NextNodesBehavior *behavior) {
    delete nextNodesBehavior;
    nextNodesBehavior = behavior;
}

std::vector<Node *> *Node::getNextNodes() {
    return nextNodesBehavior->getNextNodes(this);
}