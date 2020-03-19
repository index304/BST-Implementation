/* file: bst.c */

#include "bst.h"

void insert(Tree *treePtr, char *word){
	if ( *treePtr != NULL){
		if ( strcmp((*treePtr)->value, word) > 0) 
			insert( &((*treePtr)->left), word);
		else if (strcmp((*treePtr)->value, word) < 0)
			insert( &((*treePtr)->right), word);
	}
	else {
		*treePtr = malloc(sizeof (struct Node));
		(*treePtr)->value = malloc (strlen(word)+1); 
		
		// Check if memory is available. 
	    memoryCheckString((*treePtr)->value);
		memoryCheckTree(*treePtr);
		
		// Copy word to the vertex.
		strcpy((*treePtr)->value, word);
		
		(*treePtr)->subTree = (*treePtr)->right = (*treePtr)->left = NULL;
	}
}

void printAll(Tree t){
	if (t != NULL){
		printAll(t->left); 
		printf("%s\n", t->value);
		printAll(t->right);
	}
}


Tree *find (Tree *treePtr, char *word){
	if ((*treePtr) != NULL){
		if ( strcmp((*treePtr)->value, word) > 0) 
			return find(&((*treePtr)->left), word);
		else if (strcmp((*treePtr)->value, word) < 0)
			return find(&((*treePtr)->right), word);
	}
	return treePtr; 
}

void removeAll(Tree t){
	if ( t != NULL ){
		removeAll ( t -> left );
		removeAll ( t -> right );
		removeAll (t->subTree); 
		free (t->value); 
		free (t);
	}
}


void deleteWhenTwoChildrenExist (Tree *treePtr){
	// Three auxiliary pointners used to find the
	// correct vertex and copy the data from that vertex to *treePtr.
	Tree tmp = NULL;
	Tree wsk = (*treePtr)->right; 
	Tree pom = (*treePtr)->right; 
	
	// Remove data in Vertex. 
	removeAll((*treePtr)->subTree);
	free((*treePtr)->value);
	
	// Situation when left son of treePtr right son doesn't exist. 
	if (wsk->left == NULL){
		tmp = (*treePtr)->left; 
		
		free(*treePtr);
		
		(*treePtr) = wsk;
		(*treePtr)->left = tmp;
		return; 
	}
	
	// Finding the most left vertice in treePtr right son tree. 
	while (pom->left != NULL){
		wsk = pom;
		pom = pom->left; 
	}
	
	// Copy the right son of found vertex. 		
	wsk->left = pom->right; 
	 
	 // Alloc memory and copy value to our vertex. 
	(*treePtr)->value = malloc(strlen(pom->value)+1); 
	 
	 // Check if memory is available. 
	 memoryCheckString((*treePtr)->value);
		
	// Copy value to vertex. 
	strcpy((*treePtr)->value, pom->value);
	(*treePtr)->subTree = pom->subTree; 
	
	// Everything from pom vertex was copy, so it's time to delete it. 
	free(pom->value);
	free(pom);
}

void removeElem (Tree *treePtr, char* word){
	if ((*treePtr)== NULL )
		return; 
	
	if (strcmp((*treePtr)->value, word) > 0) 
		removeElem(&((*treePtr)->left), word);
	else if (strcmp((*treePtr)->value, word) < 0)
		removeElem(&((*treePtr)->right), word);
	else {
		// Delete Vertice without left child.
		if ((*treePtr)->left == NULL){ 
			Tree tmp = (*treePtr)->right; 
			
			removeAll((*treePtr)->subTree);
			free((*treePtr)->value);
			free(*treePtr);
			
			(*treePtr) = tmp; 
		}
		// Delete Vertice without right child.
		else if ((*treePtr)->right == NULL){ 
			Tree tmp  = (*treePtr)->left; 
			
			removeAll((*treePtr)->subTree);
			free((*treePtr)->value);
			free(*treePtr);
			
			(*treePtr) = tmp;
		}
		else {
			// Delete vertice wchich have two children. 
			deleteWhenTwoChildrenExist (treePtr);
		}		
	}	
}

// Check if memory was allocated to check obj.  
void memoryCheckTree (Tree check){
	if (check == NULL)
		exit(EXIT_FAILURE); 
}

// Check if memory was allocated to check obj.
void memoryCheckString (char *check){
	if (check == NULL)
		exit(EXIT_FAILURE);
}
