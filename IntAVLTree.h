#include <iostream>
#include <string>

class IntAVLTree
{
    private:
    class Node
    {
        public:
        //the integer stored at the node
        int value;
        //the left and right children of the node
        Node *left, *right;
        //the balance factor, used for balancing
        int bf;
        //the height of the subtree rooted at the node, used for balancing
        int height;

        Node(int new_val)
        :value{new_val},
        left{nullptr},
        right{nullptr},
        bf{0},
        height{0}
        {
        }

        //assignment operator overload
        Node& operator=(Node const&node)
        {
            if(this == &node)
            {
                return *this;
            }

            value = node.value;
            left = node.left;
            right = node.right;

            return *this;
        }
    };

    //The root of the AVL tree
    Node *root;

    //helper function for insert()
    Node* insert_helper(Node* node, int value);
    //helper function for remove()
    Node* remove_helper(Node* node, int value);
    //helper function for serialize()
    std::string serialize_helper(Node *node);
    //updates the balance factor and height for a given node
    void update(Node *node);
    //balances the AVL tree
    Node* balance(Node *node);
    //tree is left heavy, rotate right
    Node* LL_case(Node *node);
    //tree requires both a left rotation of the left child of a given
    //node and a right rotation of the given node
    Node* LR_case(Node *node);
    //tree is right heavy, rotate left
    Node* RR_case(Node *node);
    //tree requires both a right rotation of the right child of a given
    //node and a left rotation of the given node
    Node* RL_case(Node *node);
    //do a left rotation at a given node
    Node* rotate_left(Node *node);
    //do a right rotation at a given node
    Node* rotate_right(Node *node);

    public:
    IntAVLTree();

    //inserts a node containing a new value
    void insert(int value);
    //removes a node containing a given value
    void remove(int value);
    //serializes the AVL tree using a pre-order traversal
    std::string serialize();

};
