/* file: bst.h 
 * Implementation of BST Tree. 
 */
 
#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;

typedef struct Node* Tree;

/// Struct Node represents Binary Search Tree. 
/// value - value stored at the vertex
/// left, right - left and right son of the vertex
/// subTree - BST tree stored at the vertex
struct Node {
  char *value;
  Tree subTree;
  Tree left, right;
};

/// Function inserts word into tree. 
void insert(Tree *treePtr, char *word);

/// Function prints all values in tree in leksykographic order.
/// Function doesn't print values from subtree. 
void printAll(Tree t);

/// Function finds word in treePtr and return it. 
Tree *find (Tree *treePtr, char *word);

/// Function removes all vertices from tree t. 
void removeAll(Tree t);

/// Function removes data from vertex treePtr when 
/// this vertex has two sons. 
void deleteWhenTwoChildrenExist (Tree *treePtr);

/// Function removes word from tree. 
void removeElem (Tree *treePtr, char *word);

/// Check if memory was allocated to check obj.  
/// exit program if memory was not allocated. 
void memoryCheckTree (Tree check); 

/// Check if memory was allocated to check obj.  
/// exit program if memory was not allocated. 
void memoryCheckString (char *check);

#endif //BST_H

