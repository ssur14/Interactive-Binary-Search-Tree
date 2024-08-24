#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Insert an item into the binary search tree. Be sure to keep 
// the binary search tree properties. When an item is first 
// inserted into the tree the count should be set to 1. When 
// adding a duplicate string (case sensitive), rather than adding 
// another node, the count variable should just be incremented.
void BSTree::insert(const string& key) {
  Node *newNode = new Node(key);

  // Edge case:  The tree is empty
  if (root == nullptr) {
    root = newNode;
    return;
  }

  for (Node* curr = root; root != nullptr;) {
    // Edge case: If we find the key in the tree, just increment its count
    if (key == curr->key) {
      curr->count++;
      return;
    }

    // Typical case, we find a hole where this key belongs

    // ==> if we would go left and there is no child there, insert new node to left
    else if (key < curr->key) {
      if (curr->left == nullptr) {
        curr->left = newNode;
        return;
      }
      
      curr = curr->left;
    }

    // ==> if we would go right and there is no child there, insert new node to right
    else {
      if (curr->right == nullptr) {
        curr->right = newNode;
        return;
      }
      
      curr = curr->right;
    }
  }
}


// Search for a string in the binary search tree. It should 
// return true if the string is in the tree, and false otherwise.
bool BSTree::search(const string& key) const {
  for (Node *curr = root; curr != nullptr;) {
    if (key == curr->key) {
      return true;
    }

    if (key < curr->key) { // curr is on left side of tree
      if (curr->left == nullptr) return false;
      curr = curr->left;
    }

    else { // curr is on right side of tree
      if (curr->right == nullptr) return false;
      curr = curr->right;
    }
  }

  return false;
}


// Find and return the largest value in the tree. Return 
// an empty string if the tree is empty.
string BSTree::largest() const {
  Node *curr = root;

  if (curr == nullptr) { // tree is empty
    return "";
  }

  else {
    while (curr->right != nullptr) { // find rightmost node
      curr = curr->right;
    }

    return curr->key;
  }
}


// Find and return the smallest value in the tree. Return 
// an empty string if the tree is empty.
string BSTree::smallest() const {
  Node *curr = root;

  if (curr == nullptr) { // tree is empty
    return "";
  }

  else {
    while (curr->left != nullptr) { // find leftmost node
      curr = curr->left;
    }

    return curr->key;
  }
}


// Compute and return the height of a particular string in the 
// tree. The height of a leaf node is 0 (count the number of edges
// on the longest path). Return -1 if the string does not exist.
int BSTree::height(const string& key) const {
  // find the node with this key
  Node *curr = nullptr;
  for (curr = root; curr != nullptr && curr->key != key;) {
    if (key < curr->key) {
      curr = curr->left;
    }

    else {
      curr = curr->right;
    }
  }

  // run "height_of" to get the height 
  return height_of(curr);
}

// helper function to height()
int BSTree::height_of(Node* tree) const {
  // The height (length of longest path to the bottom) of an empty tree is -1
  if (tree == nullptr) return -1;

  // Otherwise, you pick the larger of the left height and the right height
  // and add one to that
  return 1 + max(height_of(tree->left), height_of(tree->right));
}


// Remove a specified string from the tree.
void BSTree::remove(const string& key) {
  return remove(nullptr, root, key);
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
}












// // helper function for remove
// void BSTree::remove(Node* parent, Node* tree, const string& key) {
//   if (tree == nullptr) { // tree is empty
//     return;
//   }

//   // find the node to remove
//   for (Node *curr = tree; curr != nullptr;) { // traverse through tree
//     if (key < curr->key) {
//         remove(curr, curr->left, key);
//       }

//       else if(key > curr->key) {
//         remove(curr, curr->right, key);
//       }
    
//     // If removing a node with a count greater than 1, just decrement the count
//     if (curr->key == key) { 
//       curr->count--;

//       if (curr->count == 0) {
//         if (curr->left == nullptr && curr->right == nullptr) {  // check if curr is a leaf
//           if (parent == nullptr) { // remove the last node from root
//             delete curr;
//             root = nullptr; 
//             return;
//           }

//           if (curr == parent->left) { // curr is the left child, remove it from parent
//             delete curr;
//             parent->left = nullptr;
//           }

//           else { // curr is the right child, remove it from parent
//             delete curr;
//             parent->right = nullptr;
//             return;
//           }
//         }

//         else if (curr->left != nullptr) { // check if curr has left subtree 
//           Node *largestKey = curr->left;

//           while (largestKey->right != nullptr) { // find largest key
//             largestKey = largestKey->right;
//           }   

//           // Copy the target information into the node we found, 
//           // set the target count to one
//           curr->key = largestKey->key;
//           curr->count = largestKey->count;
//           largestKey->count = 1;
          
//           // recursively remove it from left subtree 
//           remove(curr, curr->left, curr->key);
//           return;
//         }

//         //check if curr has right subtree
//         else if (curr->right != nullptr) {
//           Node *smallestKey = curr->right;

//           while (smallestKey->left != nullptr) { // find smallest key
//             smallestKey = smallestKey->left;
//           }

//           // Copy the target information into the node we found, 
//           // set the target count to one
//           curr->key = smallestKey->key;
//           curr->count = smallestKey->count;
//           smallestKey->count = 1;

//           // recursively remove it from right subtree 
//           remove(curr, curr->right, curr->key);
//           return;
//         }
//       }
//     }

//     return;
//   }
// }


// Traverse and print the tree in preorder notation 
void BSTree::preOrder() const {
  preOrder(root);
  cout << endl;
}

// PreOrder helper function
void BSTree::preOrder(Node* tree) const {
  // print key, do left, do right
  if (tree != nullptr) {
    cout << tree->key << "(" << tree->count << "), ";
    preOrder(tree->left);
    preOrder(tree->right);
  }
}


// Traverse and print the tree in postorder notation 
void BSTree::postOrder() const {
  postOrder(root);
  cout << endl;
}

// PostOrder helper function
void BSTree::postOrder(Node* tree) const {
  // do left, do right, print key
  if (tree != nullptr) {
    postOrder(tree->left);
    postOrder(tree->right);
    cout << tree->key << "(" << tree->count << "), ";
  }
}


// Traverse and print the tree in inorder notation 
void BSTree::inOrder() const {
  inOrder(root);
  cout << endl;
}

// InOrder helper function
void BSTree::inOrder(Node* tree) const {
  // do left, print key, do right
  if (tree != nullptr) {
    inOrder(tree->left);
    cout << tree->key << "(" << tree->count << "), ";
    inOrder(tree->right);
  }
}
