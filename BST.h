//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/10/01

#include "SSet.h"

template <class Key, class T>
class Node {
public:
  Key k;
  T data;
  Node* left;
  Node* right;
};

template <class Key, class T>
class BST : public SSet <Key,T> {
 public:
  BST();
  ~BST();
  
  //Return the number of items currently in the SSet
  virtual unsigned long size();

  //Add a new item, x, with Key k.
  // If an item with Key k already exists, overwrite it
  virtual void add(Key k, T x);

  //Remove the item with Key k. If there is no such item, do nothing.
  virtual void remove(Key k);

  //Return the item with Key k. 
  // If there is no such item, throw an exception.
  virtual T find(Key k);
  //Return true if there is an item with Key k in the table. If not,
  // return false
  virtual bool keyExists(Key k);

  //If there is a key in the set that is > k,
  // return the first such key. If not, return k
  virtual Key next(Key k);
  //If there is a key in the set that is < k,
  // return the first such key. If not, return k
  virtual Key prev(Key k);

private:
  Node<Key,T>* root;

  virtual unsigned long size(Node<Key,T>* r);
  // These are the recursive versions of each of your methods.
  // You should return the address of the new root node, whether
  // or not the root node changes.
  virtual Node<Key,T>* add(Key k, T x, Node<Key,T>* r);
  virtual Node<Key,T>* remove(Key k, Node<Key,T>* r);

  //This one returns the address of the found node, NULL
  // if not found
  virtual Node<Key,T>* find(Key k, Node<Key,T>* r);

  //Find the item in the sub-tree rooted at r which has the smallest key
  virtual Node<Key,T>* min(Node<Key,T>* r);

  //Find the item in the sub-tree rooted at r which has the largest key
  virtual Node<Key,T>* max(Node<Key,T>* r);

  //Find the next/prev node, and return its address
  virtual Node<Key,T>* next(Key k, Node<Key,T>* r);
  virtual Node<Key,T>* prev(Key k, Node<Key,T>* r);
    
  //CREATED METHOD: Used to delete all nodes, called in the destructor
  virtual Node<Key, T>* removeAll(Node<Key, T>* r);
};

/**********************
 * Previously BST.ipp *
 *********************/

#define NULL 0
#include <string>

template <class Key, class T>
BST<Key,T>::BST(){
    root = NULL;
}

template <class Key, class T>
BST<Key,T>::~BST(){
    //use a removeAll() method to delete all the nodes
    removeAll(root);
}

//My created method for removing all the nodes in the BST
template <class Key, class T>
Node<Key, T>* BST<Key,T>::removeAll(Node<Key, T>* r) {
    //Base case: No nodes connected to it
    if(r->left == NULL && r->right == NULL) {
        delete r;
    }
    //Case 1: There is a node to the left
    else if(r->left != NULL) {
        return removeAll(r->left);
    }
    //Case 2: Must be a node to the right
    else {
        return removeAll(r->right);
    }
}

//Return the number of items currently in the SSet
template <class Key, class T>
unsigned long BST<Key,T>::size(){
    //Return the private size() method using the top node
    //as the parameter
    return size(root);
}

template <class Key, class T>
unsigned long BST<Key,T>::size(Node<Key,T>* r){
    if(r == NULL) {
        return 0;
    }
    else {
        return 1 + size(r->left) + size(r->right);
    }
}

//Add a new item, x, with Key k.
// If an item with Key k already exists, overwrite it
template <class Key, class T>
void BST<Key,T>::add(Key k, T x){
    //This is the public add() method, must call the private add()
    //and add it in reference to the entire BST, no subtree
    add(k, x, root);
}

//Remove the item with Key k. If there is no such item, do nothing.
template <class Key, class T>
void BST<Key,T>::remove(Key k){
    //Calls the private remove() method, with the root node
    //as the starting reference point
    remove(k, root);
}

//Return the item with Key k.
// If there is no such item, throw an exception.
template <class Key, class T>
T BST<Key,T>::find(Key k){
    Node* tempNode = find(k, root);
    
    //returns the T data, not the node
    return tempNode->data;
}

//Return true if there is an item with Key k in the table. If not,
// return false
template <class Key, class T>
bool BST<Key,T>::keyExists(Key k){
    //COME BACK TO THIS, if find returns null, can I try to
    //access its 'k' value? Would it be null?
    Node* tempNode = find(k, root);
    
    if(tempNode->k == k) {
        return true;
    }
    else {
        return false;
    }
}

//If there is a key in the set that is > k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::next(Key k){
    Node* tempNode = next(k, root);
    
    if(tempNode == NULL) {
        return k;
    }
    else {
        return tempNode->k;
    }
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::next(Key k, Node<Key,T>* r){
    if(r == NULL) {
        return NULL;
    }
    else if(k == r->k) {
        //all nodes r->right are larger, look for the next smallest
        return min(r->right);
    }
    else if(k < r->k) {
        //keep looking for k == r->k
        return next(k, r->left);
    }
    else {
        //keep looking for k == r->k
        return next(k, r->right);
    }
}

//If there is a key in the set that is < k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::prev(Key k){
    Node* tempNode = prev(k, root);
    
    if(tempNode == NULL) {
        return k;
    }
    else {
        return tempNode->k;
    }

}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::prev(Key k, Node<Key,T>* r){
    if(r == NULL) {
        return NULL;
    }
    else if(k == r->k) {
        //all nodes r->left are smaller, look for the previous largest
        return max(r->left);
    }
    else if(k < r->k) {
        //keep looking for k == r->k
        return prev(k, r->left);
    }
    else {
        //keep looking for k == r->k
        return prev(k, r->right);
    }
}


template <class Key, class T>
Node<Key,T>* BST<Key,T>::add(Key k, T x, Node<Key,T>* r){
    if(root == NULL) {
        //Only done for the first node, makes it the root
        root->k = k;
        root->data = x;
        return root;
    }
    else if(keyExists(k) == true) {
        //key already exists, replace it with the data 'x'
        Node* tempNode = find(k, root);
        tempNode->data = x;
        return tempNode;
    }
    else if(r == NULL) {
        //Root is already null, create new node and return it
        Node<Key, T>* newNode = new Node<Key, T>;
        return newNode;
    }
    else if(k < r->k) {
        //The key is less than the current node, add to the left child
        add(k, x, r->left);
    }
    else {
        //The key is greater than the current node, add to the right child
        add(k, x, r->right);
    }
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::remove(Key k, Node<Key,T>* r){
    if(keyExists(k) == false) {
        throw std::string("In remove(), tried to remove a non-existent node");
    }
    else if(r->k == k) {
        //Found the node to delete, now more cases
        
        if(r->left == NULL && r->right == NULL) {
            //The node has no children, can just delete it and return the
            //now NULL node
            delete r;
            return NULL;
        }
        else if(r->left != NULL) {
            //The returned node/new root node for the subtree
            //should be the max of the left in this case
            //Swap the nodes and then delete the now max node
            Node<Key, T>* newNode = max(r->left);
            Key tempKey = newNode->k;
            T tempData = newNode->data;
            
            newNode->k = r->k;
            r->k = tempKey;
            
            newNode->data = r->data;
            r->data = tempData;
            
            //Eventually finds and removes the swapped node
            //we initially wanted to remove
            r->left = remove(k, r->left);
            return r;
        }
        else {
            //There are no children to the left, delete the node
            //and return newNode as the new reference child
            Node<Key, T>* newNode = r->right;
            delete r;
            return newNode;
        }
    }
    else if(k < r->k) {
        //Look for r->k == k node
        remove(k, r->left);
    }
    else {
        //Look for r-k == k node
        remove(k, r->right);
    }
}

//Recursive way of finding a key, returns the node, returns
//null if the </> tests lead to a null node.  The first
//node that is passed is the root from the public function
template <class Key, class T>
Node<Key,T>* BST<Key,T>::find(Key k, Node<Key,T>* r){
    if(r == NULL) {
        return NULL;
    }
    else if(r->k == k) {
        //Found it, return it
        return r;
    }
    else if(k < r->k) {
        return find(k, r->left);
    }
    else {
        return find(k, r->right);
    }
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::max(Node<Key,T>* r){
    //The maximum value is always the bottom right of a subtree
    //check to see if there are more to right, then return that
    if(r->right == NULL) {
        return r;
    }
    else {
        return max(r->right);
    }
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::min(Node<Key,T>* r){
    //The minimum value is always the bottom left of a subtree
    //check to see if there are more to left, then return that
    if(r->left == NULL) {
        return r;
    }
    else {
        return min(r->left);
    }
}

