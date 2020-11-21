#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

int main(int argc, string argv[])
{

  printf("\033[1;32m");
  system("figlet selection sort");
  if (argc < 2)
  {
    printf("missing arguments. reboot...\n");
    return 1;
  }
  int length = argc - 1;
  int numbers[length];
  for (int i = 0; i < length; i++)
  {

    numbers[i] = atoi(argv[i + 1]);

  }

  int s_n, s_n_p, stat; // s_n is smallest number, s_n_p is the position of the smallest number in the array
  for (int i = 0; i < length - 1; i++)
  {

    for (int j = i + 1; j < length; j++)
    {
        if (numbers[j] < numbers[j - 1])
        {
            s_n = numbers[j];
            s_n_p = j;
            stat++;
        }

    }
    if (stat > 0)
    {
        numbers[s_n_p] = numbers[i];
        numbers[i] = s_n;
    }
    stat = 0;
  }

  for (int i = 0; i < length; i++)
  {
    printf("%i. %i\n", i + 1, numbers[i]);
  }

  return 0;

}