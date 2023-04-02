// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    for (node *temp = table[index]; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long sum = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *p = fopen(dictionary, "r");
    if (p == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(p, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, word);
        word_count++;

        n->next = table[hash(word)];
        table[hash(word)] = n;
    }

    fclose(p);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}
