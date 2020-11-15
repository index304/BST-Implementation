/* Jakub Bedełek
 * File: main.c
 * File contatins main function. 
 */

#define _GNU_SOURCE

#include "task.h"


int main(void) {
   /// root - Root of the BST tree, wchich will keep all data information received
   ///        from input file.
   /// N - Estimated size of the input line. 
   /// inputLine - input Line.
   /// wrongChars - Equals 1 if input line doesn't contain wrong ascii code,
   ///              equals 0 if input line contains wrong ascii code. 
   /// readSize - Size of the input line. 
   Tree root = NULL;
   size_t N = 25;
   char *inputLine = NULL;
   int readSize; 
   
   while ((readSize = getline (&inputLine, &N, stdin)) != -1) {
    // Check if memory is available. 
    memoryCheckString(inputLine);
      
      // If input line is not a comment start processing input line. 
      if (inputLine[0] != '#'){
         processInputLine (inputLine, &root, readSize); 
      }
      
      free(inputLine); 
      inputLine = NULL; 
   }
   // Clean all data. 
   free(inputLine);
   removeAll(root);

   return 0; 
}

