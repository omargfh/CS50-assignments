#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

bool char_case(char c, char lettercase);
bool ASCII(char c);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing arguments. reboot...");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("incorrect key. reboot...");
        return 1;
    }

    bool invalid;
    bool dublicate;
    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {

        argv[1][i] = toupper(argv[1][i]);

    }
    for (int i = 0; i < length; i++)
    {
        if (!ASCII(argv[1][i]))
        {
            return 1;
        }

        for (int j = 0; j < length; j++)
        {
            if (i != j)
            {
                if (argv[1][i] == argv[1][j])
                {
                    return 1;
                }
            }
        }
    }

    string text = get_string("plaintext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        char enc_c;
        if (char_case(c, 'l'))
        {

            enc_c = argv[1][(int) c - 97];
            if (!char_case(enc_c, 'l'))
            {
                enc_c += 32;
            }
            text[i] = enc_c;

        }
        else if (char_case(c, 'u'))
        {

            enc_c = argv[1][(int) c - 65];
            if (!char_case(enc_c, 'u'))
            {
                enc_c -= 32;
            }
            text[i] = enc_c;

        }

    }
    printf("ciphertext: %s\n", text);

    return 0;

}

bool char_case(char c, char lettercase)
{

    if (lettercase == 'l' && ((int) c >= 97 && (int) c <= 122))
    {
        return true;
    }
    else if (lettercase == 'u' && ((int) c >= 65 && (int) c <= 90))
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool ASCII(char c)
{

    if (((int) c >= 65 && (int) c <= 90) || ((int) c >= 97 && (int) c <= 122))
    {

        return true;

    }
    else
    {

        return false;
    }

}