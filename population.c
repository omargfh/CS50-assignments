#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int calculate(int start_size, int end_size);

int main(void) {

    int start_size = get_int("Start Size: ");
    int end_size = get_int("End Size: ");
    printf("Years: %i\n", calculate(start_size, end_size));

}

int calculate(int start_size, int end_size) {

    int year = 0;
    while(start_size < end_size) {
        start_size = start_size + (start_size / 3) - (start_size / 4);
        year++;
    }
    return year; 

}
