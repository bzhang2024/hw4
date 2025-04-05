#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value> //extends class Node
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{
  //note: leaves created with balance 0
}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key, Value>* n);

    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n); 
    void removeFix(AVLNode<Key, Value>* node, int diff);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    /*
    pseudocode
    - look at key of new_item
    - walk the tree to the correct node, and insert the newitem as its child
    - look at parent p
    - if balance(p) = -1 or 1, set it to 0 (the balance of grandparent doesn't change)
    - if balance(p) = 0, call insertFix because the grandparent may now be unbalanced
    */

    AVLNode<Key, Value>* node = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    
    //empty tree case
    if (this->root_ == nullptr){
      this->root_ = node; 
      return; 
    }

    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    AVLNode<Key, Value>* prev = nullptr; 
    
    //find place of insertion
    while (current != nullptr){
      prev = current; 
      if (node->getKey() < current->getKey()){
        current = current->getLeft();
      }
      else if (node->getKey() > current->getKey()){
        current = current->getRight();
      }
      else { //same key, so rewrite value
        current->setValue(node->getValue());
        delete node; //deallocate
        return; 
      }
    }

    //after exiting from loop, right spot
    //insert - update pointers
    node->setParent(prev);
    if (node->getKey() < prev->getKey()){
      prev->setLeft(node);
    }
    else {
      prev->setRight(node);
    }

    //fix balance of the tree
    if (prev->getBalance() == -1){ 
      prev->setBalance(0);
    }
    else if (prev->getBalance() == 1){ 
      prev->setBalance(0);
    }
    else if (prev->getBalance() == 0) { //balance is 0, so now -1 or 1
      if (prev->getLeft() == node){ //inserted left 
        prev->updateBalance(-1);
      }
      else {
        prev->updateBalance(1);
      }
      insertFix(prev, node); 
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* node){
  /*
  pseudocode
  - if p is null, return
  - let g = parent(p) grandparent
  - update g's balance
  - case 1: b(g) == 0, return
  - case 2: b(g) == -1 insertFix bc parent of g may be out of balance
  - case 3: b(g) == -2
      if zigzig then rotate 
      if zigzag then double rotate
  */

  if (parent == nullptr){
    return;
  }

  AVLNode<Key, Value>* gparent = parent->getParent();
  if (gparent == nullptr){
    return;
  }
  //update g
  if (gparent->getLeft() == parent){
    gparent->updateBalance(-1);
  }
  else {
    gparent->updateBalance(1);
  }

  //go through cases
  if (gparent->getBalance() == 0){
    return;
  }
  else if (gparent->getBalance() == 1 || gparent->getBalance() == -1){ //parent of gparent could be out of balance, work up ancestor chain
    insertFix(gparent, parent);
  }

  //parent is left child of gparent
  else if (gparent->getBalance() == -2){
    if (parent->getBalance() == -1){ //zigzig case
      rotateRight(gparent);
      gparent->setBalance(0); parent->setBalance(0);
    }
    else { //zigzag case
      rotateLeft(parent);
      rotateRight(gparent);
      
      switch (node->getBalance()){
        case -1:
          parent->setBalance(0); gparent->setBalance(1); node->setBalance(0);
          break;
        case 0:
          parent->setBalance(0); gparent->setBalance(0); node->setBalance(0);
          break;
        case 1:
          parent->setBalance(-1); gparent->setBalance(0); node->setBalance(0);
          break;
      }
    }
  }
  //p is right child of gparent
  else if (gparent->getBalance() == 2){
    if (parent->getBalance() == 1){ //zigzig case
      rotateLeft(gparent);
      gparent->setBalance(0); parent->setBalance(0);
    }
    else { //zigzag case
      rotateRight(parent);
      rotateLeft(gparent);
      switch (node->getBalance()){
        case 1:
          parent->setBalance(0); gparent->setBalance(-1); node->setBalance(0);
          break;
        case 0:
          parent->setBalance(0); gparent->setBalance(0); node->setBalance(0);
          break;
        case -1:
          parent->setBalance(1); gparent->setBalance(0); node->setBalance(0);
          break;
      }
    }
  }

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    /*
    pseudocode
    - find node by walking tree
    - if n has 2 children, swap positions with pred
    - let p = parent(n)
    - if p != nullptr
    - then if n is left child, diff = 1, if n is right child, diff = -1
    - update pointers and delete n
    - removeFix(p, diff) to patch tree
    */

    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (node == nullptr){
      //nothing to remove
      return;
    }

    if (node->getLeft() != nullptr && node->getRight() != nullptr){
      AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
      nodeSwap(node, pred);
    }

    AVLNode<Key, Value>* parent = node->getParent();

    //either 1 or 0 child case
    AVLNode<Key, Value>* child = nullptr;
    if (node->getLeft() != nullptr){
      child = node->getLeft(); 
    }
    else{
      child = node->getRight();
    }

    if (child != nullptr){
      child->setParent(parent);
    }

    int diff = 1;
    if (parent == nullptr){
      this->root_ = child; 
    }
    else { 
      if (node == parent->getRight()){
        diff = -1; 
        parent->setRight(child); 
      }
      else {
        parent->setLeft(child);
        //diff stays 1
      }
    }
    delete node;
    removeFix(parent, diff);    
}

template<typename Key, typename Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key, Value>* node, int diff){
  /*
  pseudocode
  - if n is null, return
  - fk
  */

  if (node == nullptr){
    return;
  }
  AVLNode<Key, Value>* parent = node->getParent();

  if (parent == nullptr){
    return;
  }


  int nextdiff = -1;  
  if (parent->getLeft() == node){
    nextdiff = 1;
  }
  //ndiff stays -1 if right child

  if (node->getBalance() + diff == 0){
    node->setBalance(0);
    removeFix(parent, nextdiff); //RECURSE
  }
  else if (node->getBalance() + diff == 1){
    node->setBalance(1);
  }
  else if (node->getBalance() + diff == -1){
    node->setBalance(-1);
  }
  //left child taller
  else if (node->getBalance() + diff == -2){
    AVLNode<Key, Value>* child = node->getLeft(); //taller of the 2 children
    
    if (child->getBalance() == -1){ //zigzig
      rotateRight(node);
      node->setBalance(0); child->setBalance(0);
      removeFix(parent, nextdiff); //RECURSE up the ancestor chain
    }
    else if (child->getBalance() == 0){ //zigzig w 2 nodes
      rotateRight(node);
      node->setBalance(-1); child->setBalance(1);
    }
    else { //cbal = 1, zigzag
      AVLNode<Key, Value>* gchild = child->getRight(); 
      rotateLeft(child);
      rotateRight(node);
      switch (gchild->getBalance()){
        case 1:
          node->setBalance(0); child->setBalance(-1); gchild->setBalance(0);
          break;
        case 0:
          node->setBalance(0); child->setBalance(0); gchild->setBalance(0);
          break;
        case -1:
          node->setBalance(1); child->setBalance(0); gchild->setBalance(0);
          break;
      }
      removeFix(parent, nextdiff); //RECURSE
    }
  }
  
  //right child taller
  if (node->getBalance() + diff == 2){
    AVLNode<Key, Value>* child = node->getRight(); //taller of the 2 children
    if (child->getBalance() == 1){ //zigzig
      rotateLeft(node);
      node->setBalance(0); child->setBalance(0);
      removeFix(parent, nextdiff); //RECURSE
    }
    else if (child->getBalance() == 0){ //zigzig w 2 nodes
      rotateLeft(node);
      node->setBalance(1); child->setBalance(-1);
    }
    else { //cbal = -1, zigzag
      AVLNode<Key, Value>* gchild = child->getLeft(); 
      rotateRight(child);
      rotateLeft(node);
      switch (gchild->getBalance()){
        case -1:
          node->setBalance(0); child->setBalance(1); gchild->setBalance(0);
          break;
        case 0:
          node->setBalance(0); child->setBalance(0); gchild->setBalance(0);
          break;
        case 1:
          node->setBalance(-1); child->setBalance(0); gchild->setBalance(0);
          break;
      }
      removeFix(parent, nextdiff);
    }
  }
}


template<typename Key, typename Value>
void AVLTree<Key, Value>:: rotateLeft(AVLNode<Key, Value>* node){
  /*
  xyz (x is right child of y is right child of z)
  - parent of y = parent of z, parent of z (left/right) child = y
  - z right child = y left child, y left child parent = z
  - y left child = z, z parent = y

  note: gchild node does not necessarily exist in case of zigzag
  */

  AVLNode<Key, Value>* rchild = node->getRight(); 
  AVLNode<Key, Value>* parent = node->getParent(); //could be null

  rchild->setParent(parent);
  if (parent == nullptr){
    this->root_ = rchild; 
  }
  else {
    if (node == parent->getRight()){
    parent->setRight(rchild);
    }
    else { //node is left child
      parent->setLeft(rchild);
    }
  }
  
  node->setRight(rchild->getLeft());
  if (rchild->getLeft() != nullptr){
    (rchild->getLeft())->setParent(node); 
  }
  

  rchild->setLeft(node);
  node->setParent(rchild);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>:: rotateRight(AVLNode<Key, Value>* node){
  /*
  xyz (z is grandparent, x is left child of y, y is left child of z)
  - update 6 pointers/3 relationships
  - y parent = z parent, z parent (left/right) child = y
  - z right child same, z left child = y right child, y right child's parent = z
  - y right child = z, z parent = y
  - x children same
  */

  AVLNode<Key, Value>* lchild = node->getLeft(); 
  AVLNode<Key, Value>* parent = node->getParent(); //could be null

  lchild->setParent(parent);
  if (parent == nullptr){
    this->root_ = lchild; 
  }
  else {
    if (node == parent->getRight()){
    parent->setRight(lchild);
    }
    else { //node is left child
      parent->setLeft(lchild);
    }
  }

  node->setLeft(lchild->getRight());
  if (lchild->getRight() != nullptr) { ////lchild->getRight() could be null
    lchild->getRight()->setParent(node);
  } 

  lchild->setRight(node);
  node->setParent(lchild); 
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}



#endif
