# Dictionary_Using_BST
In this assignment, you are required to implement a spell checking system 
based on a binary search tree. You will be given a file containing all 
language words. The file would contain one word per line. At the beginning, 
print the height of the generated Binary Search Tree. Your program should 
prompt the user to enter a sentence to check its spelling. 
For each word in the entered sentence, you check whether the word exists in 
the binary search tree. 
(a) If the word exists, you will print that the word is correct. 
(b) If the word does not exist, you will print three suggestions for the 
correct word: 
- The word in the leaf node you reached before declaring that the word does 
not exist. 
- The word in the inorder predecessor of that leaf node. 
- The word in the inorder successor of that leaf node. 
