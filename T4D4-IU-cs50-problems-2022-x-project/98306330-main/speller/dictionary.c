// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//declare variables
unsigned int word_count = 0;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO/////////////////////////////////////////////////////////////////////////////////////////////////////////////////check
    //ハッシュ関数の何処にあるかインデックスを取得する
    //wordのハッシュ値を取得して、ハッシュテーブルのノードを確認していく
    int index = hash(word);
    node *n = table[hash(word)];
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        //次のノードを確認するようにしたい
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO//////////////////////////////////////////////////////////////////////////////////////////////////////////////////load
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Opening the file is missed");
        return false;
    }
    //word prototype
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        hash_value =  hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //load関数にword_countを追加しカウントさせる
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO//////////////////////////////////////////////////////////////////////////////////////////////////////////////////unload
    //線形探索
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        node *cursor = n;
        node *tmp = n;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
