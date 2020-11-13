#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

bool ASCII(char c);
float avg(int averaged, int averaged_over, int range);
float coleman_index(float L, float S);

int main(void)
{

    string text = get_string("Text: ");
    int sentences = 0;
    int words = 1;
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        if (text[i] == ' ' && i != 0 && i != n - 1)
        {

            words ++;

        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }
        else if (ASCII(text[i]))
        {

            letters++;

        }

    }

    float L = avg(letters, words, 100);
    float S = avg(sentences, words, 100);
    float grade = coleman_index(L, S);
    if (grade == 16)
    {

        printf("Grade 16+\n");

    }
    else if (grade < 0.5)
    {

        printf("Before Grade 1\n");

    }
    else
    {

        printf("Grade %.0f\n", grade);

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

float avg(int averaged, int averaged_over, int range)
{

    return (float) averaged / averaged_over * range;

}

float coleman_index(float L, float S)
{

    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 15.5)
    {

        return index;

    }
    else
    {

        return 16;

    }

}