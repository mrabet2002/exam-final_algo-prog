#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_MAX_SIZE 1000
#ifndef VARCHAR_H
#define VARCHAR_H

typedef struct varchar_t
{
    char *txt;
    int max_size;
    int size;
} varchar_t;

varchar_t create_varchar(size_t max_size);
void scan_varchar(varchar_t *ptr_varchar);
int find_word(const varchar_t *const ptr_varchar, const char *word, int n);
void replace_word(varchar_t *const ptr_varchar, const char *word1, const char *word2, int n);

#endif