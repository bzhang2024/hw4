#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool checkDepth(Node* node, int& depth);

bool equalPaths(Node * root)
{
    int depth = 0;
    return checkDepth(root, depth);
}

bool checkDepth(Node* node, int& depth)
{
    if (node == nullptr)
    {
        depth = 0; //empty tree
        return true;
    }
    if (node->left == nullptr && node->right == nullptr) //leaf node
    {
        depth = 1;
        return true; 
    }


    int leftDepth = 0, rightDepth = 0;
    bool leftEqual = checkDepth(node->left, leftDepth);
    bool rightEqual = checkDepth(node->right, rightDepth);

    if (!leftEqual || !rightEqual) { //left and right subtrees meet check
        return false;
    }

    // If one child exists, use its depth
    if (node->left == nullptr) {
        depth = rightDepth + 1;
        return true;
    }
    if (node->right == nullptr) {
        depth = leftDepth + 1;
        return true;
    }

    //2 children
    if (leftDepth != rightDepth){
      return false; 
    }

    //update depth by reference
    depth = leftDepth + 1; //depth of current node 
    return true; 

}

