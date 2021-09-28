// Implements a dictionary's functionality
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];
int dictionarySize = 0;

// Hashes word to a n== 0)umber
unsigned int hash(const char *word)
{
    // Function should take a string and return an index
    // This hash function adds the ASCII values of all characters in     the word together
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // opening directory file
    FILE *file = fopen(dictionary, "r");
    //base check
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    //create arrar of chars to store words
    char tmpword[LENGTH + 1];
    //read strings from the file one at a time and store them at tmpword
    while (fscanf(file, "%s", tmpword) != EOF)
    {
        //creating a new node for each word
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            unload();
            return false;
        }
        //copying word (string) into node
        strcpy(newnode->word, tmpword);

        //hashing value
        int hash_value = hash(tmpword);
        //inserting node into the list at hash location
        newnode->next = table[hash_value];
        table[hash_value] = newnode;
        dictionarySize++;
    }
    fclose(file);
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //take the word and hash it
    int hash_value = hash(word);
    //access the linked list at that hash value
    node *head = table[hash_value];
    node *cursor = head;
    //traverse linked list at that hash value
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
