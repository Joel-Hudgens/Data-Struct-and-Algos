//************************************************************************
// ASU CSE310 Assignment #6 Spring 2024
// Joel Hudgens
// 1224491216
// Description: This class represents a Red Black Tree
// A RBT (red black tree) is a binary search tree that balances itself by using RED and BLACK nodes
// There are 5 rules to a RBT, and every time we add a node, we must preserve these rules in order to maintain the RBT
// A RBT has a height of at most 2*log(n+1), which allows for all major operations to take place in THeta(logn) running time
//************************************************************************

// include the relevant header file
#include "RedBlackTree.h"
#include <string>

using namespace std;

//*******************************************************************
// constructor
RedBlackTree::RedBlackTree()
{
      root = NULL;            //initialize tree with an empty root node
}

//*******************************************************************
// destructor
RedBlackTree::~RedBlackTree()
{
      int nodeSize = deleteNode(root);

      cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
// Accessor for the root of the red-black tree
Node *RedBlackTree::getRoot()
{
      return root;
}

//*******************************************************************
// delete the sub-tree rooted at 'node' and return number of nodes deleted
// This should be defined as a recursive function
// Calculate the size of the tree and delete every node
int RedBlackTree::deleteNode(Node *node)
{
      //Base case
      if (node == nullptr)
      {
            return 0;
      }

      // Delete left and right subtrees
      int leftSize = deleteNode(node->leftChild);
      int rightSize = deleteNode(node->rightChild);

      // Delete current node
      delete node;

      // Total nodes deleted = left + right + root
      return 1 + leftSize + rightSize;
}

//****************************************************************
// This is the general BST insertion operation.
// It does not care about the color of the newly added node.
void RedBlackTree::insertNode(Node *node)
{

      Node *current = root;
      Node *par = nullptr;

      // Traverse the tree to find the correct position for insertion
      while (current != nullptr)
      {
            par = current;
            if (node->vin < current->vin)       //if our node is less than the next
            {
                  current = current->leftChild;       //go left
            }
            else
            {
                  current = current->rightChild;
            }
      }
      node->parent = par;

      // If the tree is empty then the inserted node is the root
      if (par == nullptr)
      {
            root = node;
      }
      else if (node->vin < par->vin)
      {                                   // Insert to the left
            par->leftChild = node;
      }
      else
      {
            par->rightChild = node;    // Insert to the right
      }
      node->leftChild = NULL;
      node->rightChild = NULL;
      node->color = "RED";

      fixUp(node);            //We need to fix any RBT viiolations caused by the insertion of this RED node
}

//*******************************************************************
// At beginning, each newly added node will always be RED,
// this may violate the red-black tree property #4. fixUp()
// function will restore the property.
void RedBlackTree::fixUp(Node *z)
{
      while (z != root && z->parent->color == "RED")
      { // while our parent's color is still red

            if (z->parent == z->parent->parent->leftChild)
            {

                  Node* y = z->parent->parent->rightChild;
                 
                  if (y != nullptr && y->color == "RED")
                  { // CASE 1: We flip colors of z, z.p, and y
                        z->parent->color = "BLACK";
                        y->color = "BLACK";
                        z->parent->parent->color = "RED";
                        z = z->parent->parent;
                  }
                  
                  else  //the uncle(y) is nullptr or BLACK (black either way)
                  {
                        if (z == z->parent->rightChild)
                        { // CASE 2.1: Convert close uncle into far uncle by left rotating
                              z = z->parent;
                              leftRotate(z);
                        }
                        z->parent->color = "BLACK"; // CASE 2.2: Switch colors and right rotate (terminal caase)
                        z->parent->parent->color = "RED";
                        rightRotate(z->parent->parent);
                  }
            }

            else
            { // This else block is the same as the first block, but left and right are flipped
                  //This is because we have to check the case for left child
                  Node* y = z->parent->parent->leftChild;

                  if (y != nullptr && y->color == "RED")
                  {
                        z->parent->color = "BLACK";
                        y->color = "BLACK";
                        z->parent->parent->color = "RED";
                        z = z->parent->parent;
                  }
                  else
                  {
                        if (z == z->parent->leftChild)
                        {
                              z = z->parent;
                              rightRotate(z);
                        }

                        z->parent->color = "BLACK";
                        z->parent->parent->color = "RED";
                        leftRotate(z->parent->parent);
                  }
            }
      } // end while loop
      root->color = "BLACK"; // make sure root in BLACK
}

//*****************************************************
// This function print the pre-order traversal of the
// subtree rooted at 'node'.It's a recursive function
void RedBlackTree::preOrderTraversal(Node *node)
{
      if (node == nullptr){ // base case
            return;
      }

      // root
      print(node);
      // recurse left
      preOrderTraversal(node->leftChild);
      // recurse right
      preOrderTraversal(node->rightChild);
}

//**************************************************
// This function print the in-order traversal of the
// subtree rooted at 'node'.It's a recursive function
void RedBlackTree::inorderTraversal(Node *node){
      if (node == nullptr){ // base case
            return;
      }

      // recurse left
      inorderTraversal(node->leftChild);
      // root
      print(node);
      // recurse right
      inorderTraversal(node->rightChild);
}

//**************************************************
// This function print the post-order traversal of the
// subtree rooted at 'node'.It's a recursive function
void RedBlackTree::postOrderTraversal(Node *node){
      if (node == nullptr){ // base case
            return;
      }

      // recurse left
      postOrderTraversal(node->leftChild);
      // recurse right
      postOrderTraversal(node->rightChild);
      // root
      print(node);
}

//**************************************************************
// This function returns a pointer points to the minimum node from
// the current sub-tree rooted at 'node'. It should be designed as
// a recursive function
Node* RedBlackTree::findMinimumNode(Node *node){
      // Base case
      if (node == nullptr)
            return nullptr;

      // If the left child exists, recursively keep going left
      if (node->leftChild != nullptr)
            return findMinimumNode(node->leftChild);

      // return the node that we end on
      return node;
}

//**************************************************************
// This function returns a pointer points to the maximum node from
// the current sub-tree rooted at 'node'. It should be designed as
// a recursive function
Node* RedBlackTree::findMaximumNode(Node *node){
      // Base case
      if (node == nullptr)
            return nullptr;

      // If the right child exists, recursively keep going right
      if (node->rightChild != nullptr)
            return findMaximumNode(node->rightChild);

      // return the node that we end on
      return node;
}

//**************************************************************
// This function search the tree for a given key of a Car
// Note: key is the combination of vin, model and make of the Car
// It returns a pointer points to the node if founded; otherwise it returns NULL
Node* RedBlackTree::treeSearch(int vin, string model, string make) {
      Node* temp = root;
      string tempKey = to_string(vin) + model + make;

      while(temp != nullptr && compareNodes(temp,tempKey) != 0){              //while temp is not found and not null
            if(compareNodes(temp,tempKey) == 1){            //If the node is less than, go left
                  temp = temp->leftChild;
            }
            else{
                  temp = temp->rightChild;                   //Otherwise, go right
            }
      }
      return temp;
}

//****************************************************
// This function left-rotate the BST rooted at 'node'
// Think about this as picking up a node to left or right of 'node'
// and then re hanging the sub tree from that node
void RedBlackTree::leftRotate(Node *node){
      Node* y = node->rightChild;
      node->rightChild = y->leftChild;    //turn y’s left subtree into x’s right subtree

      if (y->leftChild != nullptr){
            y->leftChild->parent = node;
      }
      y->parent = node->parent;           // link x’s parent to y

      if(node->parent == NULL){           //Update the root if 'node' is the root
            root = y;
      }
      else if(node == node->parent->leftChild){
            node->parent->leftChild = y;
      }
      else{
            node->parent->rightChild = y;//If 'node' is the right child of its parent
      }
      y->leftChild = node;
      node->parent = y;
}

//***************************************************
// This function right-rotate the BST rooted at 'node'
// write your own code according to red-black tree definition
void RedBlackTree::rightRotate(Node *node){
    Node* y = node->leftChild;
    node->leftChild = y->rightChild;    // Turn y’s right subtree into x’s left subtree

    if (y->rightChild != nullptr){
        y->rightChild->parent = node;
    }
    y->parent = node->parent;           // Link x’s parent to y

    if(node->parent == NULL){             //Update the root if 'node' is the root
        root = y;
    }
    else if(node == node->parent->rightChild){
        node->parent->rightChild = y;
    }
    else{ //If 'node' is the left child of its parent
        node->parent->leftChild = y;
    }
      y->rightChild = node;
      node->parent = y;
}


//**************************************************************
// This function finds the predecessor of the given 'node'
// it prints the relevant predecessor info. on screen and also
// return a pointer that points to the predecessor
Node* RedBlackTree::findPredecessorNode(Node *node){
    if(node->leftChild != nullptr){
        return findMaximumNode(node->leftChild);            //if the left child exists then return the max node in its subtree
    }
    Node* y = node->parent;

    while(y != nullptr && node == y->leftChild){            //traverse up to find the predecessor
        node = y;
        y = y->parent;
    }

    return y;
}

//**************************************************************
// This function finds the successor of the given 'node'
// it prints the relevant successor info. on screen and also return
// a pointer that points to the successor node
Node* RedBlackTree::findSuccessorNode(Node *node){
      if(node->rightChild != nullptr){
            return findMinimumNode(node->rightChild);       //if the right child exists then return the minimum node in its subtree
      }
      Node* y = node->parent;

      while(y != nullptr && node == y->rightChild){         //traverse up to find the successor
            node = y;
            y = y->parent;
      }

      return y;
}



//You will notice the next methods from treeMinimum() to treeInsert() are void and have a cooresponding function that already does that thing
//We are using these as printer functions and al so that we can call our methods from main without creating new nodes everywhere
//We can call the helper functions directly with what the user enters (model,make,vin)... or with root if we want it done on the entire tree




//****************************************************************
// This function find the minimum node of the entire red-black tree
// It print out the minimum node info. on screen if tree is not empty
// or print Tree is empty. No Minimum. message on screen.
void RedBlackTree::treeMinimum(){
      Node* min = findMinimumNode(root);

      if(root == nullptr){
            cout<< "tree is empty\n";
      }
      else{
            cout<< "The MINIMUM is:\n";
            print(min);
      }
}

//**************************************************************
// This function find the maximum node of the entire red-black tree
// It print out the maximum node info. on screen if tree is not empty
// or print Tree is empty. No Maximum. message on screen.
void RedBlackTree::treeMaximum(){
      Node* max = findMaximumNode(root);

      if(root == nullptr){
            cout<< "tree is empty\n";
      }
      else{
            cout<< "The MAXIMUM is:\n";
            print(max);
      }
}

//****************************************************************************
// This function print out the pre-order traversal of the entire red-black tree
// write your own code according to red-black tree definition
void RedBlackTree::treePreorder(){
      if(root == nullptr){
            cout<< "tree is empty\n";
            return;
      }else{
            preOrderTraversal(root);
      }
      
}

//***************************************************************************
// This function print out the in-order traversal of the entire red-black tree
void RedBlackTree::treeInorder(){
      if(root == nullptr){
            cout<< "tree is empty\n";
            return;
      }
      else{
            inorderTraversal(root);
      }

}


//*****************************************************************************
// This function print out the post-order traversal of the entire red-black tree
void RedBlackTree::treePostorder(){
      if(root == nullptr){
            cout<< "tree is empty\n";
            return;
      }
      else{
            postOrderTraversal(root);
      }

}

//******************************************************************
// Given a Car key, this function first check whether the
// Car is inside the tree or not, if it is inside, it will print
// its predecessor info. on screen, if not, it print an error message
void RedBlackTree::treePredecessor(int vin, string model, string make){
      Node* found = treeSearch(vin,model,make);

      if (found != nullptr){
            cout << left;
                  cout << setw(8) << vin
                  << setw(12) << model
                  << setw(12) << make
                  << setw(12) << "is FOUND.\n";
      }
      else{
            cout << "NOT FOUND";
            return;
      }
      Node* predecessor = findPredecessorNode(found);

      if(predecessor != nullptr){
            cout << "Its Predecessor is:\n";
            print(predecessor);
      }
      else{
            cout << "Its Predecessor does NOT EXIST\n";
      }

}

//******************************************************************
// Given a Car key, this function first check whether the
// Car is inside the tree or not, if it is inside, it will print
// its successor info. on screen, if not, it print an error message
void RedBlackTree::treeSuccessor(int vin, string model, string make){
      Node* found = treeSearch(vin,model,make);

      if (found != nullptr){
            cout << left;
                  cout << setw(8) << vin
                  << setw(12) << model
                  << setw(12) << make
                  << setw(12) << "is FOUND.\n";
      }
      else{
            cout << "NOT FOUND";
            return;

      }
      Node* successor = findSuccessorNode(found);

      if(successor != nullptr){
            cout << "Its Successor is:\n";
            print(successor);
      }
      else{
            cout << "Its Successor does NOT EXIST\n";
      }
}

//**************************************************************
// This function create a node from the given info., then insert
// the node inside the red-black tree. Note: at beginning, the newly
// added node should always be 'RED'
void RedBlackTree::treeInsert(int vin, string model, string make, double price){
      Node* newNode = new Node;
      newNode->vin = vin;
      newNode->model = model;
      newNode->make = make;
      newNode->price = price;             //Initialize new node

      insertNode(newNode);                //insert the node then fix any RBT violations 
}

//******************************************************************
// Given a 'node', this function prints vin, model, make only... no newline
void RedBlackTree::printVinModelMake(Node *node)
{
      cout << left;
      cout << setw(8) << node->vin
           << setw(12) << node->model
           << setw(12) << node->make;
}

//******************************************************************
// Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(8) << node->vin
           << setw(12) << node->model
           << setw(12) << node->make
           << setw(10) << fixed << setprecision(2) << node->price;
      cout << right << setw(7) << node->color << endl;
}

//**************************************************************
// Given a Node 'node1', this function compares it with another
// node's key.
// key is a string combination of vin + model + make
// It returns a negative number if in alphabetical order, key is
// in front of 'node'; otherwise it returns a positive number
int RedBlackTree::compareNodes(Node *node, string key){
      int nodeVin = node->vin;
      string model = node->model;
      string make = node->make;

      string keyFromNode = to_string(nodeVin) + model + make;   //make a key from the node we are given

      int comparison = keyFromNode.compare(key);                  //compare the the two keys in alphabetical order

      if(comparison < 0) {
            return -1;              
      }
      else if (comparison > 0) {
            return 1;
      }
      else{
            return 0;
      }
}