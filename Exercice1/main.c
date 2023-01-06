#include <stdio.h>
#include "varchar.h"

int main(int argc, char const *argv[])
{
    varchar_t v = create_varchar(STR_MAX_SIZE);
    char word1[100], word2[100];
    int n;
    scan_varchar(&v);
    printf("%s\n", v.txt);
    printf("Donnez la sous chaine a remplacer : ");
    gets(word1);
    printf("La sous chaine dans qulle occurence : ");
    scanf("%d", &n);
    printf("Vous voulez la remplacer par quoi ? ");
    gets(word2);
    getchar();
    replace_word(&v, word1, word2, n);
    printf("\nApres remplacer la sous chaine '%s' dans l'occurence %d par '%s' : \n%s\n", word1, n, word2, v.txt);
    return 0;
}
