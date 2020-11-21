#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>


int main(int argc, string argv[])
{

  printf("\033[1;32m");
  system("figlet bubble sort");
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
  int stat = 0;
  for(int i = 0; stat < length - 1; i++)
  {

    int n_f = numbers[i];
    int n_s = numbers[i + 1];
    if (n_s < n_f)
    {
      numbers[i + 1] = n_f;
      numbers[i] = n_s;
    }
    else
    {
      stat++;
    }
    if (stat == length - 1)
    {
      break;
    }
    else if (i == length - 2)
    {
      i = -1;
      stat = 0;
    }

  }

  for (int i = 0; i < length; i++)
  {
    printf("%i. %i\n", i + 1, numbers[i]);
  }

  return 0;

}
