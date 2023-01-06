#include "varchar.h"

varchar_t create_varchar(size_t max_size)
{
    varchar_t varchar;
    varchar.max_size = max_size;
    varchar.size = 0;
    varchar.txt = (char *)malloc(varchar.max_size * sizeof(char));
    varchar.txt[0] = '\0';
    return varchar;
}
void scan_varchar(varchar_t *ptr_varchar)
{
    char str[STR_MAX_SIZE];
    int i = 0;
    printf("Veuillez saisire votre texte : ");
    gets(str);
    while (str[i] != '\0')
    {
        ptr_varchar->txt[i] = str[i];
        i++;
        if ((ptr_varchar->max_size - 1) == i)
            break;
    }
    ptr_varchar->txt[i] = '\0';
    ptr_varchar->size = i;
}
int find_word(const varchar_t *const ptr_varchar, const char *word, int n)
{
    int i = 0, j = 0, occ = 0, wordSize = strlen(word);

    if (strlen(word) > 0)
    {
        for (i = 0; i < ptr_varchar->size; i++)
        {
            if (word[j] == ptr_varchar->txt[i])
            {
                j++;
                if (j == wordSize)
                {
                    occ++;
                    if (occ == n)
                        return (i + 1) - j;
                    else
                        j = 0;
                }
            }
            else
                j = 0;
        }
    }
    return -1;
}
void replace_word(varchar_t *const ptr_varchar, const char *word1, const char *word2, int n)
{
    int foundWordIndex = find_word(ptr_varchar, word1, n),
        word1Size = strlen(word1),
        word2Size = strlen(word2);
    if (foundWordIndex != -1)
    {
        int i, leftWordIndex = foundWordIndex + word1Size,
               leftWordSize = (ptr_varchar->size - (leftWordIndex));
        char *tmp = (char *)malloc(leftWordSize * sizeof(char));
        for (i = 0; i < leftWordSize; i++)
            tmp[i] = ptr_varchar->txt[i + leftWordIndex];
        for (i = 0; i < word2Size; i++)
        {
            if (i + foundWordIndex == ptr_varchar->max_size - 1)
                break;
            ptr_varchar->txt[i + foundWordIndex] = word2[i];
        }
        ptr_varchar->size = foundWordIndex + word2Size;
        for (i = 0; i < leftWordSize; i++)
        {
            if (ptr_varchar->size++ == ptr_varchar->max_size)
                break;
            ptr_varchar->txt[ptr_varchar->size - 1] = tmp[i];
        }
        ptr_varchar->txt[ptr_varchar->size] = '\0';
    }
}