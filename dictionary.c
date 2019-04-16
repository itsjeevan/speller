// Implements a dictionary's functionality

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "dictionary.h"
#include <ctype.h>

// Linked list struct
typedef struct sllist {
    char word[LENGTH + 1];
    struct sllist *next;
} sllnode;


// Hash function
int hash_function(const char *hash_word) {

    int output = 0;

    for (int i = 0; hash_word[i] != '\0'; i++) {

        if (isalpha(hash_word[i])) {
            output += toupper(hash_word[i]) - 'A';
        }
    }

    return output % 516;
}


// Global variables
bool load_complete = false;
sllnode *hashtable[516] = { NULL };


// Returns true if word is in dictionary else false
bool check(const char *word) {

    sllnode *trav = hashtable[hash_function(word)];

    while (trav != NULL) {

        if (strcasecmp(trav->word, word) == 0) {
            return true;
        }

        trav = trav->next;
    }

    return false;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) {

    FILE *fp;
    fp = fopen(dictionary, "r");
    if (fp == NULL) {
        return false;
    }

    char dictionary_word[LENGTH+1];

    while (fscanf(fp, "%s", dictionary_word) != EOF) {

        sllnode *new_node = malloc(sizeof(sllnode));

        if (new_node == NULL) {
            return false;
        }

        strcpy(new_node->word, dictionary_word);
        int x = hash_function(new_node->word);

        new_node->next = hashtable[x];
        hashtable[x] = new_node;
    }

    fclose(fp);
    load_complete = true;
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) {

    if (load_complete) {

        unsigned int word_counter = 0;
        sllnode *trav = NULL;

        for (int i = 0; i < 516; i++) {

            trav = hashtable[i];

            if (trav == NULL) {
                continue;
            }

            while (trav != NULL) {
                word_counter++;
                trav = trav->next;
            }
        }

        return word_counter;
    }
    else {
        return 0;
    }
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void) {

    sllnode *trav = NULL;
    sllnode *temp = NULL;

    for (int i = 0; i < 516; i++) {

        trav = hashtable[i];

        if (trav == NULL) {
            continue;
        }

        while (trav != NULL) {
            temp = trav;
            trav = trav->next;
            free(temp);
        }
    }

    load_complete = false;
    return true;
}
