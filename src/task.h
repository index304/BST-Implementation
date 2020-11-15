/* file: task.h
 * This file process the input line, supports commands ADD, DEL, PRINT, CHECK
 * and uses BST tree to store information from input line.
 */
 
#ifndef TASK_H
#define TASK_H

#include "bst.h"

/// Maximum number of words in correct input line. 
#define MAX_SIZE 4

/// This function processing input line. 
void processInputLine(char *inputLine, Tree *root, int readSize);

/// Function returns 1 if given parameter is white space. 
int checkWhiteSpace(char inputChar);

#endif // TASK_H
