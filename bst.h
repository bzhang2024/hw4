#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(nullptr),
    right_(nullptr)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr); //constructor
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void deleteNodes(Node<Key, Value>* n);
    int checkBalance(Node<Key, Value>* n) const; 

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr) :
    current_(ptr)
{
    // TODO
    // DONE 
    //initializer list
}

/**
* A default constructor that initializes the iterator to nullptr.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(nullptr)
{
    // TODO
    //DONE

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // DONE

    return (current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    //DONE

    return (current_ != rhs.current_); 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    //DONE
    //current is the Node<key, value> pointer

    //sucessor is right most node of right subtree
    //otherwise, is parent
    //if node is the rightmost node, then no sucessor

    if (current_ == nullptr){
      return *this;
    }
    //there is a right subtree
    if (current_->getRight() != nullptr){
      current_ = current_->getRight();
      while (current_->getLeft() != nullptr){
        current_ = current_->getLeft();
      }
    }
    //no right subtree
    else {
      Node<Key, Value>* parent = current_->getParent();
      while (parent != nullptr && parent->getLeft() != current_){ //current is in rightsubtree of parent so parent < current
        current_ = parent;
        parent = parent->getParent();
      }
      current_ = parent; //either nullptr or the current node will be a predesessor of parent, so parent is the succesor of current
    }

    return *this; 
  
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to nullptr.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() :
  root_(nullptr)
{
    // TODO
    // DONE initializer list

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    //DONE
    //delete the nodes in the tree
    clear(); 

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == nullptr;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode()); //returns a pointer to smallest node i think
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(nullptr);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == nullptr) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == nullptr) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // DONE
    const Key key = keyValuePair.first;
    const Value value = keyValuePair.second;

    // If the tree is empty crate new
    if (root_ == nullptr) {
        root_ = new Node<Key, Value>(key, value, nullptr);
        return;
    }

    // Start at the root and traverse the tree to find the correct position
    Node<Key, Value>* current = root_;
    Node<Key, Value>* parent = nullptr;

    while (current != nullptr) { //while no empty spot
        parent = current;

        //if key exists, update value
        if (key == current->getKey()) {
            current->setValue(value);
            return;
        }

        // walk the tree
        if (key < current->getKey()) {
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }

    // Create new node, update pointers
    Node<Key, Value>* newNode = new Node<Key, Value>(key, value, parent);
    //std::cout << "Here is the key " << newNode->getKey() << " " << newNode->getValue() << std::endl;
    if (key < parent->getKey()) {
        parent->setLeft(newNode);
    } 
    else {
        parent->setRight(newNode);
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    //DONE
    //use internal find
    Node<Key, Value>* nodeToRemove = internalFind(key);
    if (nodeToRemove == nullptr){
      return;
    }

    //2 child case
    if (nodeToRemove->getLeft() != nullptr&& nodeToRemove->getRight() != nullptr){
      Node<Key, Value>* pred = predecessor(nodeToRemove);
      nodeSwap(nodeToRemove, pred); //nodeSwap swaps all pointers, also updates root_ if needed
    }

    //at this point, should be 0 or 1 child case
    Node<Key, Value>* child; 
    if (nodeToRemove->getLeft() != nullptr){
      child = nodeToRemove->getLeft(); 
    }
    else {
      child = nodeToRemove->getRight(); //could potentially be nullptr
    }
    //child->setParent(nodeToRemove.getParent()); 

    //update parent/child pointers
    Node<Key, Value>* parent = nodeToRemove->getParent(); 
    //check for case where nodeToRemove has no parent i.e. root
    if (parent == nullptr){
        root_ = child; // remove root
    }
    else {
      if (parent->getLeft() == nodeToRemove){
        parent->setLeft(child); //promote child
      }
      else {
        parent->setRight(child);
      }
    }
    
    if (child != nullptr){
      child->setParent(parent);
    }

    delete nodeToRemove; 



}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    //predecessor is the right most node of the left subtree
    if (current == nullptr){
      return nullptr;
    }
    //there is a left subtree
    if (current->getLeft() != nullptr){
      current = current->getLeft();
      while (current->getRight() != nullptr){
        current = current->getRight();
      }
    }
    //no left subtree, so find first node where current is part of its right subtree
    else {
      Node<Key, Value>* parent = current->getParent();
      while (parent != nullptr && current == parent->getLeft()){ //current is in leftsubtree of parent so parent > current
        current = parent;
        parent = parent->getParent();
      }
      current = parent; //either nullptr or the current node will be a suceessor of parent, so parent is a predesecor to current
    }

    return current; 

}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
  //DONE
  //trees have no cycles, so can implement recursively 
  deleteNodes(root_);
  root_ = nullptr; 
}

template<typename Key, typename Value> 
void BinarySearchTree<Key, Value>::deleteNodes(Node<Key, Value>* node){
  if (node == nullptr){
    return; 
  }
  deleteNodes(node->getLeft());
  deleteNodes(node->getRight());

  delete node; 
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // DONE
    //smallest node is the leftmost

    if (root_ == nullptr){
      return nullptr; 
    }

    Node<Key, Value>* current = root_; 

    while (current->getLeft() != nullptr){
      current = current->getLeft();
    }
    return current; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or nullptr if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    //DONE

  Node<Key, Value>* current = root_;
  
  while (current != nullptr) { 
    Key ckey = current->getKey(); 
    if (key == ckey){ //found the right node
      return current; 
    }
    if (ckey < key){
      current = current->getLeft();
    }
    else {
      current = current->getRight(); 
    }
  }
  return nullptr;  //nullptr
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    //DONE
    //balanced tree - for every node, the height of its left subtree is within 1 of the height of its right subtree
    return (checkBalance(root_) != -1); //check if it's balanced
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::checkBalance(Node<Key, Value>* node) const { 
  if (node == nullptr){
    return 0; //height of 0
  }

  int rightHeight = checkBalance(node->getRight());
  int leftHeight = checkBalance(node->getLeft());

  if (leftHeight == -1 || rightHeight == -1){
    return -1; //tree is unbalanced
  }
  if (std::abs(rightHeight-leftHeight) > 1){
    return -1; //tree is unbalanced
  }
  //update height for current subtree
  return std::max(leftHeight, rightHeight) + 1;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == nullptr) || (n2 == nullptr) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != nullptr && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != nullptr && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != nullptr && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != nullptr && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != nullptr && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != nullptr && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != nullptr && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != nullptr && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != nullptr && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != nullptr && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != nullptr && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != nullptr && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
