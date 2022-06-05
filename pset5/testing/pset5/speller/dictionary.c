// Implements a dictionary's functionality

#include <stdbool.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "string.h"
#include "strings.h"
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


 // Number of words in dictionary 
unsigned int word_counter = 0;

void check_memory(node *ptr);

// Number of buckets in hash table
const unsigned int TABLE_SIZE = 10000;

// Hash table
node *table[TABLE_SIZE];



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    
    int hash_value = hash(word);
    // Traversing linked list
    node *cursor = table[hash_value];
    while(cursor != NULL)
    {
        if( strcasecmp(word, cursor->word) == 0 )
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    /*
    Author(s) name: djb2 
    Date: 1991
    Title of program: djb2 hash
    Code version: N/A
    Type: hash function
    Web address: http://www.cse.yorku.ca/~oz/hash.html
    */
    unsigned int hash = 5381;
    int c;
    
    
    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        
        
    return hash % TABLE_SIZE;
    //return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //**open dictionary file**//
    FILE *dict = fopen(dictionary, "r");
    // check file validity
    if (dict == NULL)
    {
        printf("Could not open file \n");
        return -1;
    }
    
    //**Reading strings from file**//
    
    char *dict_word = malloc(sizeof(char) * LENGTH);
    // check file validity
    if (dict_word == NULL)
    {
        printf("Not enough memory \n");
        return -1;
    }
    
    while(fscanf(dict, "%s", dict_word) != EOF)
    {
        //**Creating a new node**//
        
        //allocating memory for new node
        node *n = malloc(sizeof(node));
        check_memory(n);
        //adding data to the node
        strcpy(n -> word, dict_word);
        
        //setting node pointer to NULL
        n -> next = NULL;
        
        //**Hashing word through hash function**//

        // getting hash code for a word
        unsigned int hash_code = hash(dict_word);
        printf("word: %s \n", dict_word);
        printf("hash_code: %i\n", hash_code);
        printf("current word number: %d \n", word_counter);
        //** Inserting Node into hash table **//
        
        // check table[hash_code] is empty
        if(table[hash_code] == NULL)
        {
            table[hash_code] = n;
        }
        //collision
        else
        {
            // temporary node
            node *tmp_n = malloc(sizeof(node));
            check_memory(tmp_n);
            tmp_n = table[hash_code];
            while(tmp_n->next)
            {
                tmp_n = tmp_n -> next;
            }
            tmp_n -> next = n;
        }
        //increment no.words
        size();
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    (word_counter)++;
    return word_counter;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}


void check_memory(node *ptr)
{
    /*
    check for memory space
    return nothing
    */
    if(ptr == NULL)
    {
        printf("Not enough memory \n");
        exit(0);
    }
}