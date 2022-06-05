// Implements a dictionary's functionality

#include <stdbool.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "string.h"
#include "strings.h"
#include "ctype.h"
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
const unsigned int TABLE_SIZE = 100;

// Hash table
node *table[TABLE_SIZE];



// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hash word to obtain ahash value
    int hash_value = hash(word);
    // Access linked list
    node *cursor = table[hash_value];
    //Traverse linked list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
            return true;
        cursor = cursor -> next;
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
    
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    
    return hash % TABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //#Open dictionary file
    FILE *dict_file = fopen(dictionary, "r");
    
    // Check for NULL
    if (dict_file == NULL)
        return false;
        
    //Reading strings from th file
    char word[LENGTH + 1];
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        //#Creating new node
        
        //Allocating memory for new node
        node *n = malloc(sizeof(node));
        // Check for NULL
        if (n == NULL)
        {
            return false;
        }
        //Copy string to the node
        strcpy(n -> word, word);
        // set next node to null
        n -> next = NULL;
        //#Hashing word through hash function
        
        // Get hash value for word
        unsigned int hash_value = hash(word);
        
        //n -> next = table[hash_value];
        //table[hash_value] = n;
    
        //#Inserting Node into hash table
        //Check if node is empty
        
        if (table[hash_value] == NULL)
        {
            table[hash_value] = n;
        }
        //if not then collision
        else
        {
            node *tmp_n = malloc(sizeof(node));
            
            if (tmp_n == NULL)
            {
                return false;
            }
            
            tmp_n = table[hash_value];
            
            while (tmp_n -> next)
            {
                tmp_n = tmp_n -> next;
            }

            tmp_n -> next = n;
        }
    
        //Increment no.words
        word_counter++;
        //printf("current word number: %d \n", word_counter);
    }
    //close file
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //return number of words
    if (word_counter > 0)
    {
        return word_counter;
    }
    else
    {
        return 0;
    }
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // Move tmp_cursor into cursor node
            node *tmp_cursor = cursor;
            // move cursor to next node
            cursor = cursor -> next;
            //free tmp_cursor node
            free(tmp_cursor);
        }
        // check if end of the node and list
        if (cursor == NULL && i == TABLE_SIZE - 1)
        {
            free(cursor);
            return true;
        }
    }
    return false;
}

