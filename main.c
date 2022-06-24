#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char* data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(char* value)
{
    Node* node = malloc(sizeof(Node));
    node->data = malloc(strlen(value)+1);
    node->left = node->right = NULL;
    strcpy(node->data,value);
    return node;
}

Node* insert(Node* root, char* word)
{
    if(root == NULL)
        return newNode(word);
    if(strcasecmp(word,root->data) < 0)
        root->left = insert(root->left,word);
    else if(strcasecmp(word,root->data) > 0)
        root->right = insert(root->right,word);
    else   //To avoid insert duplicates if they exist
        return root;
    return root;
}

Node* search(Node* root, char* key)
{
    if(root == NULL)
        return NULL;
    if(strcasecmp(key,root->data) == 0)
        return root;
    else if(strcasecmp(key,root->data) < 0)
        return search(root->left, key);
    else
        return search(root->right, key);
}

int countNodes(Node* root)
{
    if(root == NULL)
        return 0;
    else
        return 1+countNodes(root->left)+countNodes(root->right);
}

int max(int x, int y)
{
    return x>y?x:y;
}

int heightOfTree(Node* root)
{
    if(root == NULL)
        return -1;
    else
        return 1+max(heightOfTree(root->left), heightOfTree(root->right));
}

Node* maximumOfTree(Node* root)
{
    if(root == NULL)
        return NULL;
    while(root->right != NULL)
        root = root->right;
    return root;
}

Node* minimumOfTree(Node* root)
{
    if(root == NULL)
        return NULL;
    while(root->left != NULL)
        root = root->left;
    return root;
}

Node* getFirstSuggestion(Node* root, char* word)
{
    while(root)
    {
        if(strcasecmp(word,root->data) < 0)
        {
            if(root->left == NULL)
                return root;
            else
                root = root->left;
        }
        else if(strcasecmp(word,root->data) > 0)
        {
            if(root->right == NULL)
                return root;
            else
                root = root->right;
        }
    }
    return root;
}

Node* getPredecessor(Node* root, Node* firstSuggestion)
{
    Node* predecessor = NULL;
    if(firstSuggestion->left != NULL)
        return maximumOfTree(firstSuggestion->left);
    else
    {
        while(root)
        {
            if(strcasecmp(firstSuggestion->data, root->data) < 0)
                root = root->left;
            else if(strcasecmp(firstSuggestion->data, root->data) > 0)
            {
                predecessor = root;
                root = root->right;
            }
            else
                break;
        }
    }
    return predecessor;
}

Node* getSuccessor(Node* root, Node* firstSuggestion)
{
    Node* successor = NULL;
    if(firstSuggestion->right != NULL)
        return minimumOfTree(firstSuggestion->right);
    else
    {
        while(root)
        {
            if(strcasecmp(firstSuggestion->data, root->data) < 0)
            {
                successor = root;
                root = root->left;
            }
            else if(strcasecmp(firstSuggestion->data, root->data) > 0)
                root = root->right;
            else
                break;
        }
    }
    return successor;
}

Node* readFile()
{
    FILE* fp = fopen("EN-US-Dictionary.txt","r");
    if(!fp)
    {
        printf("File doesn't exist");
        exit(-1);
    }
    Node* root = NULL;
    char word[25];
    while(!feof(fp))
    {
        fscanf(fp,"%s",word);
        root = insert(root,word);
    }
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    fclose(fp);
    return root;
}

int main()
{
    Node* root = readFile();
    printf("Size = %d \n",countNodes(root));
    printf("..................................\n");
    printf("Height = %d \n",heightOfTree(root));
    printf("..................................\n");
    printf("Enter a sentence:\n");
    char sentence[200];
    gets(sentence);
    char* token = strtok(sentence," \n");
    while(token!=NULL)
    {
        Node* word = search(root, token);
        if(word!=NULL && strcasecmp(token,word->data) == 0)
            printf("%s - CORRECT\n",token);
        else
        {
            printf("%s - Incorrect, Suggestions : ",token);
            Node* firstSuggestion = getFirstSuggestion(root,token);
            printf("%s ",firstSuggestion->data);
            Node* successor = getSuccessor(root,firstSuggestion);
            printf("%s ",successor->data);
            Node* predecessor = getPredecessor(root,firstSuggestion);
            printf("%s\n",predecessor->data);
        }
        token=strtok(NULL," \n");
    }
    return 0;
}
