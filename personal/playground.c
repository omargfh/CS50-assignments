#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

#undef strlen
int strlength(char *string);

int main (void)
{
    char *string = "Hello";
    printf("Number of characters: %i\n", strlength(string));

    char *t = malloc(5);
    printf("%s\n", t);

    char *name = malloc(126);
    scanf("%s", name);
    printf("%s\n", name);
    name = realloc(name, (strlen(name) + 1) * sizeof(char));
    printf("%s\n", name);
    free(name); free(t);
}

int strlength(char *string)
{
    int char_count = 0;
    for (int count = 0; *(string + count) != '\0'; count++)
    {
        char_count++;
    }
    return char_count;
}