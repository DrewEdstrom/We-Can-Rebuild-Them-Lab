#include <algorithm>
#include "IntAVLTree.h"

using namespace std;

IntAVLTree::IntAVLTree()
:
root{nullptr}
{
}

//inserts a node containing a new value
void IntAVLTree::insert(int value)
{
    root = insert_helper(root, value);
}

//helper function for insert()
IntAVLTree::Node* IntAVLTree::insert_helper(Node* node, int value)
{
    if (node == nullptr)
    {
        return new Node(value);
    }

    if (value < node->value)
    {
        node->left = insert_helper(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insert_helper(node->right, value);
    }
    else
    {
        return node; // Duplicate values not allowed
    }

    update(node);
    return balance(node);
}

//removes a node containing a given value
void IntAVLTree::remove(int value)
{
    root = remove_helper(root, value);
}

//helper function for remove()
IntAVLTree::Node* IntAVLTree::remove_helper(Node* node, int value)
{
    if (node == nullptr)
    {
        throw invalid_argument("Value not found!");
    }

    if (value < node->value)
    {
        node->left = remove_helper(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = remove_helper(node->right, value);
    }
    else
    {
        // Node with only one child or no child
        if (node->left == nullptr || node->right == nullptr)
        {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        
        // Node with two children: Find the in-order predecessor
        Node* successor = node->left;
        while (successor->right != nullptr)
        {
            successor = successor->right;
        }

        node->value = successor->value;
        node->left = remove_helper(node->left, successor->value);
    }

    if (node == nullptr) return node;

    update(node);
    return balance(node);
}

//serializes the AVL tree using a pre-order traversal
string IntAVLTree::serialize()
{
    return serialize_helper(root);
}

//helper function for serialize()
string IntAVLTree::serialize_helper(Node *node)
{
    if(node == nullptr)
    {
        return "nil";
    }

    string left_serialized{serialize_helper(node->left) + ","};
    string right_serialized{serialize_helper(node->right)};

    return to_string(node->value) + "," + left_serialized + right_serialized;
}

//updates the balance factor and height for a given node
void IntAVLTree::update(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    int left_height = (node->left == nullptr) ? -1 : node->left->height;
    int right_height = (node->right == nullptr) ? -1 : node->right->height;

    node->height = 1 + max(left_height, right_height);
    node->bf = right_height - left_height;
}

//balances the AVL tree
IntAVLTree::Node* IntAVLTree::balance(Node *node)
{
    if(node == nullptr) return nullptr;

    if(node->bf == -2)
    {
        if(node->left->bf <= 0)
        {
            return LL_case(node);
        }
        else
        {
            return LR_case(node);
        }
    }
    else if(node->bf == 2)
    {
        if(node->right->bf >= 0)
        {
            return RR_case(node);
        }
        else
        {
            return RL_case(node);
        }
    }

    return node;
}

//tree is left heavy, rotate right
IntAVLTree::Node* IntAVLTree::LL_case(Node *node)
{
    return rotate_right(node);
}

//tree requires both a left rotation of the left child of a given node and
//a right rotation of the given node
IntAVLTree::Node* IntAVLTree::LR_case(Node *node)
{
    node->left = rotate_left(node->left);
    return LL_case(node);
}

//tree is right heavy, rotate left
IntAVLTree::Node* IntAVLTree::RR_case(Node *node)
{
    return rotate_left(node);
}

//tree requires both a right rotation of the right child of a given node and
//a left rotation of the given node
IntAVLTree::Node* IntAVLTree::RL_case(Node *node)
{
    node->right = rotate_right(node->right);
    return RR_case(node);
}

//do a left rotation at a given node
IntAVLTree::Node* IntAVLTree::rotate_left(Node *node)
{
    Node *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    update(node);
    update(new_parent);

    return new_parent;
}

//do a right rotation at a given node
IntAVLTree::Node* IntAVLTree::rotate_right(Node *node)
{
    Node *new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    update(node);
    update(new_parent);

    return new_parent;
}
