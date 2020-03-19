/* file: task.c */
 
#include "task.h"

/********** Definition of all new funtion implemented in this file ************/

/// Function starts commands ADD, DEL, PRINT CHECK
/// words[] - Array containing words from input line in input order. 
/// treeVer - Pointner to actually processing BST tree vertice.
/// wordsNumber - Number of words entered in input line.
void startAllCommands (Tree *treeVer, char *words[], int wordsNumber);	

/// Parameters for next five funtions mean:
/// words[] - Array containing words from input line in input order. 
/// treeVer - Pointner to actually processing BST tree vertice.
/// wordsNumber - Number of words entered in input line. 
/// iWord - Number of actually processing word. 


/// Function adds on tree words from input line. 
void processADD (Tree *treeVer, char *words[], int wordsNumber, int iWord); 

/// Function deletes vertice with value as same as last input word in line 
/// or all tree if only input word in line is "DEL". 
void processDEL (Tree *treeVer, char *words[], int wordsNumber, int iWord); 

/// Function checks if last word in input line exists. 
void processCHECK (Tree *treeVer, char *words[], int wordsNumber, int iWord); 

/// Additional function for CHECK parameter with "*", wchich pass through every
/// vertice in tree (or subtreee) and starts function processCHECK in every
/// vertice. 
void passEveryVer (Tree *treeVer, char *words[], int wordsNumber, int iWord); 

/// Function prints all values in first layer of tree if only input word is PRINT  
/// or prints all values in wordsNumber layer in subtree of vertice wchich contain
/// value as same as last word in input line.   
void processPRINT (Tree *treeVer, char *words[], int wordsNumber, int iWord); 

/// Function return min from two numbers - a and b. 
int min (int a, int b);

/// Check if ascii code of the letter is lesser than 33. 
/// Returns 1 if yes, 0 if not. 
int asciiCodeLessThan33 (char letter);

/********** End of definition all new funtion implemented in this file *********/

// elementExist - equals 1 if searching element exist in file
// or 0 if searching element doesn't exist in file. 
// This variable is used in funtions responsible for correct
// work of "CHECK" command. 
int elementExist = 0;

int checkWhiteSpace (char inputChar){
	int n = (int)inputChar;
	return (n == 32 || n == 9 || n == 11 || n == 12 || n == 13 || n == 10);
}

void processInputLine (char *inputLine, Tree *root, int readSize){
	// wordsNumber - number of words entered in input line
	// wordBeginPos - position of the begin of the word in input line
	// prevWhiteSpace - equals 1 if previous character was white space
	//                  or 0 in opposite situtation
	// words[MAX_SIZE] - array containg words from input line in input order
	int wordsNumber = 0;
	int wordBeginPos = 0;    
	int prevWhiteSpace = 1;   
	char *words[MAX_SIZE];
	
	// Process the input line character by character to get the words entered. 
	for (int i = 0; i < readSize; i++){
		if (prevWhiteSpace && checkWhiteSpace(inputLine[i]))
			continue; 
		else if (!prevWhiteSpace && checkWhiteSpace(inputLine[i])){
			// Check correctness of current letter ascii code and number of words. 
			if(wordsNumber == MAX_SIZE || (checkWhiteSpace(inputLine[i]) != 1 &&
               asciiCodeLessThan33(inputLine[i]))){
				wordsNumber = MAX_SIZE+1;
				break;
			}
			words[wordsNumber] = NULL;
			words[wordsNumber] = malloc(i-wordBeginPos+1);
			// Check if memory is available. 
			memoryCheckString(words[wordsNumber]);
			
			// Copy word from input line to words array. 
			strncpy(words[wordsNumber], inputLine+wordBeginPos, i-wordBeginPos); 
			words[wordsNumber][i-wordBeginPos] = '\0';
			
			wordsNumber++;
			prevWhiteSpace = 1;
			wordBeginPos = i; 
		} 
		else { 		// Current character is not a white space. 
			if (prevWhiteSpace)
				wordBeginPos = i; 
			prevWhiteSpace = 0; 
		}
	}
	// If the number of word is not great than MAX_SIZE start processing the 
	// entered words. 
	if (wordsNumber > MAX_SIZE)
		fprintf(stderr, "ERROR\n");
	else if (wordsNumber != 0)
		startAllCommands(root, words, wordsNumber); 
	
	for(int i = 0; i < min(wordsNumber, MAX_SIZE); i++)
		free (words[i]);
}

void startAllCommands (Tree *root, char *words[], int wordsNumber){
	// Start word number in the launched functions. 
	int iWord = 1;  

	// Remove All if the only input word is DEL
	if (wordsNumber == 1 && strcmp(words[0], "DEL") == 0){
		removeAll(*root);
		*root = NULL;
		printf("OK\n");
	}
	// Print error if the only input word is not PRINT. 
	else if (wordsNumber == 1 && strcmp(words[0], "PRINT") != 0)
		fprintf(stderr, "ERROR\n");
	// Runs function adding words into the tree. 
	else if (wordsNumber > 1 && strcmp(words[0], "ADD") == 0){
	    processADD(root, words, wordsNumber, iWord);
		printf("OK\n");
	}
	// Runs function deleting the last word (from input line) from the tree. 
	else if (wordsNumber > 1 && strcmp(words[0], "DEL") == 0){
		processDEL(root, words, wordsNumber-1, iWord);
		printf("OK\n");
	}
	// Runs functions to check if a given word exists in the tree. 
	else if  (wordsNumber > 1 && strcmp(words[0], "CHECK") == 0){
		if (strcmp(words[wordsNumber-1], "*") == 0)
			fprintf(stderr, "ERROR\n");
		else{ 
			processCHECK(root, words, wordsNumber, iWord); 
			if (elementExist == 1)
				printf("YES\n");
			else 
				printf("NO\n");
			elementExist = 0;
		}
	}
	// Prints all values from correct subtree in leksykographic order.
	else if (wordsNumber > 0 && strcmp(words[0], "PRINT") == 0){
		if (wordsNumber == MAX_SIZE)
			fprintf(stderr, "ERROR\n");
		else 
			processPRINT(root, words, wordsNumber, iWord);
	} 
	else
		fprintf(stderr, "ERROR\n");
}

void processADD (Tree *treeVer, char *words[], int wordsNumber, int iWord){
	// Checks if the currently used word number is smaller than the number
	// of words.
	if (iWord < wordsNumber){
		// We are looking for a word at tree "treeVer". 
		Tree *tmp = find(treeVer, words[iWord]); 
		
		// If word doesn't exist, it will be inserted to the tree. 
		if(*tmp == NULL){
			insert(tmp, words[iWord]);
		}
		// ADD next word to the subtree of current vertex. 
		processADD(&((*tmp)->subTree), words, wordsNumber, iWord+1); 
	}
}

void processDEL (Tree *treeVer, char *words[], int wordsNumber, int iWord){
	// Checks if the currently used word number is smaller than the number
	// of words.
	if (iWord < wordsNumber){
		// We are looking for a word at tree "treeVer". 
		Tree *tmp = find(treeVer, words[iWord]); 
		
		if (*tmp == NULL)
			return; 
		// We are looking for next word in a subtree of current vertex.  
		processDEL(&((*tmp)->subTree), words, wordsNumber, iWord+1);
	}
	else{
		// Delete vertex containing "word" value.
		removeElem (treeVer, words[iWord]);
	}
}

void passEveryVer (Tree *treeVer, char *words[], int wordsNumber, int iWord){
	Tree tmp = *treeVer;
	
	// Going through every vertex in "treeVer" tree.  
	if (tmp != NULL && elementExist == 0){
		passEveryVer(&(tmp->left), words, wordsNumber, iWord); 
		// Looking for next word in current subtree. 
		processCHECK(&(tmp->subTree), words, wordsNumber, iWord+1);
		passEveryVer(&(tmp->right), words, wordsNumber, iWord); 
	}
}

void processCHECK (Tree *treeVer, char *words[], int wordsNumber, int iWord){
	// Checks if the currently used word number is smaller than the number
	// of words and checks if the word you are looking for has already been found.
	if (iWord < wordsNumber && elementExist == 0){
		if (strcmp(words[iWord], "*") == 0){
			// Going through every vertex in "treeVer" tree. 
			passEveryVer(treeVer, words, wordsNumber, iWord); 
		}
		else{
			// Searches for the word in the tree.
			Tree *tmp = find(treeVer, words[iWord]); 
			if (*tmp == NULL){
				return; 
			}
			else if (*tmp != NULL && iWord == wordsNumber-1){
				// The word exists, so we can stop searching further.
				elementExist = 1; 
			}
			else{
				// Looking for the next word in the subtree.
			    processCHECK(&((*tmp)->subTree), words, wordsNumber, iWord+1);	
			}
		}
	}
}

void processPRINT (Tree *treeVer, char *words[], int wordsNumber, int iWord){
	// Checks if the currently used word number is smaller than the number
	// of words.
	if (iWord < wordsNumber){
		// Searches for the word in the tree.
		Tree *tmp = find(treeVer, words[iWord]);
		if (*tmp != NULL){
			processPRINT(&((*tmp)->subTree), words, wordsNumber, iWord+1);
		}
	}
	else{
		printAll(*treeVer);
	}
}

int min (int a, int b){
	if (a < b)
		return a;
	return b; 
}

/// Check if ascii code of the letter is lesser than 33. 
/// Returns 1 if yes, 0 if not. 
int asciiCodeLessThan33 (char letter){
   int decASCIICode = (int)letter;
   
   return (decASCIICode < 33 && decASCIICode >= 0);
}

