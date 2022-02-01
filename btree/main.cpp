#include <iostream>
#include "BTree.hpp"
#include "../vector/utils.hpp"

using namespace ft;
using namespace std;

#define COUNT 20

template<class T>
void print2DUtil(BTree<T> *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->getRight(), space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout << root->getValue() <<"\n";
 
    // Process left child
    print2DUtil(root->getLeft(), space);
}
 
// Wrapper over print2DUtil()
template <class T>
void print2D(BTree<T> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


int main()
{
	BTree<int> node(0);
	BTree<int> node1(1, &node);
	BTree<int> node3(3);
	BTree<int> node2(2, &node1, &node3);
	BTree<int> node5(5);
	BTree<int> node7(7);
	BTree<int> node6(6, &node5, &node7);
	BTree<int> node4(4, &node2, &node6);

	// node.insert(node1, node);
	// node.insert(node2, node);
	// node.insert(node3, node);
	// node.insert(node4, node);
	// node.insert(node5, node);
	// node.insert(node6, node);

	print2D(&node4);

	return (0);
}
