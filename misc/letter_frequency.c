/******************************************************************************
 *
 * This programs creates a sorted map for letters in a specified sequence
 *
*******************************************************************************/

#include <stdio.h>
#include <string.h>

int main()
{
    char string[26] = "etaoinshrdlcumwfgypbvkjxqz";
    char alpha[26]  = "abcdefghijklmnopqrstuvwxyz";
    printf("{");
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (alpha[i] == string [j])
            {
                printf("%i", j);
                if (i != 25)
                {
                    printf(", ");
                }
            }
        }
    }
    printf("}");
}
