#include <iostream>
#include "IntAVLTree.h"

using namespace std;

int main()
{
    IntAVLTree tree;
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    cout << "\n\n" << tree.serialize();

    tree.remove(4);
    tree.remove(3);
    tree.remove(8);
    tree.remove(5);
    cout << "\n\n" << tree.serialize() << "\n\n";

    return 0;
}
