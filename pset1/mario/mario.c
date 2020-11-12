#include <cs50.h>
#include <stdio.h>

void build_shape(int height);
void print_blanks(int height, int count);
void print_hashes(int hash_count);
int get_positive_int(string content);


int main(void)
{
    // prompt user for height
    int height = get_positive_int("Height: ");

    // passes height to build_shape function
    build_shape(height);

    return 0;

}

int get_positive_int(string content)
{

    int height;
    do
    {
        height = get_int("%s", content);
    }
    while (height < 1 || height > 8);
    return height;

}

void build_shape(int height)
{

    for (int i = 0; i < height; i++)
    {

        int count = i + 1;
        print_blanks(height, count);
        print_hashes(count);
        printf("  ");
        print_hashes(count);
        printf("\n");


    }

}

void print_blanks(int height, int count)
{

    for (int j = 0; j < height - count; j++)
    {

        printf(" ");

    }

}

void print_hashes(int hash_count)
{

    for (int j = 0; j < hash_count; j++)
    {

        printf("#");

    }

}