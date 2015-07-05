#ifndef TREE_BINARYTREE_BINARYTREE_H_
#define TREE_BINARYTREE_BINARYTREE_H_

#include <vector>

class Node;
class TraversalTask;

class BinaryTree {
public:
    BinaryTree();
    /*
    Delete all Nodes in the tree.
    */
    ~BinaryTree();
    /*
    Please add all Nodes before operating on them, including setRoot, insert, remove and swap.
    If Node.id is smaller than zero (the default value), BinaryTree will assign a new id to the Node.
    Do not modify Node.id after adding it to BinaryTree.
    Adding a Node with the same id as another Node added before
    will replace the older Node with the newly added Node.
    */
    void addNode(Node *node);
    /*
    @param  id  An integer not smaller than zero.
    */
    Node *getNodeById(int id);
    Node *getNodeRandomly();
    /*
    Randomly connect the added Nodes to form a binary tree.
    */
    virtual void initializeRandomly();
    void setRoot(Node *node);
    void setRoot(int nodeId);
    Node *getRoot();
    /*
    Insert node between position and position.getLeftNode().

    CAUTION: In derived class of BinaryTree, if dynamic_cast is performed
             on the input Nodes, please check whether the cast pointer is 0
             because BinaryTree also use this method while the input Nodes
             are not derived class of Node.
    */
    virtual void insertLeftNode(Node *node, Node *position);
    void insertLeftNode(int nodeId, int positionId);
    /*
    Insert node between position and position.getRightNode().

    CAUTION: In derived class of BinaryTree, if dynamic_cast is performed
             on the input Nodes, please check whether the cast pointer is 0
             because BinaryTree also use this method while the input Nodes
             are not derived class of Node.
    */
    virtual void insertRightNode(Node *node, Node *position);
    void insertRightNode(int nodeId, int positionId);
    /*
    Remove a Node by swapping with its leftNode or rightNode recursively
    until no child exists, and then detaching the Node.
    @param  replaceWithRightNode    If true, swap with leftNode, or swap with
                                    rightNode unless there is no leftNode.
    */
    void removeNode(Node *node, bool replaceWithLeftNode);
    void removeNode(int nodeId, bool replaceWithLeftNode);
    /*
    Remove a Node randomly and insert it as another randomly selected Node's
    left Node.
    WARNING: If the BinaryTree has only one Node, the method will run into an
    infinite loop.
    */
    void removeAndInsertLeftNodeRandomly();
    /*
    Remove a Node randomly and insert it as another randomly selected Node's
    left Node.
    WARNING: If the BinaryTree has only one Node, the method will run into an
    infinite loop.
    */
    void removeAndInsertRightNodeRandomly();
    /*
    CAUTION: In derived class of BinaryTree, if dynamic_cast is performed
             on the input Nodes, please check whether the cast pointer is 0
             because BinaryTree also use this method while the input Nodes
             are not derived class of Node.
    */
    virtual void swapNodes(Node *node1, Node *node2);
    void swapNodes(int node1Id, int node2Id);
    void swapNodesRandomly();
    /*
    Traverse the Nodes in dfs order. How the Nodes return their next Nodes
    and what to do when traversing each Node are determined by the NodeBehavior
    of each Node.
    */
    void traverseDfs(Node *start, TraversalTask *task);
    void traverseDfs(int startId, TraversalTask *task);
    /*
    A factory method that creates an object of BinaryTree.
    A subclass of BinaryTree SHOULD override it such that it returns an object of
    the subclass.
    The method is used in copy() to create an object of the right class.
    */
    virtual BinaryTree *createBinaryTree();
    /*
    Copy the tree and the Nodes added to the tree.
    For a subclass of BinaryTree, call BinaryTree::copy() inside copy().
    If an object of a BinaryTree's subclass is composed of objects of Node's subclass, the Node's
    subclass's copy will be called.
    */
    virtual BinaryTree *copy();
    /*
    FOR DEBUG
    */
    std::vector<Node *> *getNodes();

private:
    std::vector<Node *> *nodes;
    Node *head;

    /*
    Return random integer in [0, range).
    */
    int randint(int range);
    /*
    Return true or false randomly.
    */
    bool randbool();
    /*
    Get the index of node in nodes. Return -1 if not found.
    */
    int getIndexOf(std::vector<Node *> *nodes, Node *node);
};

#endif