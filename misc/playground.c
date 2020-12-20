#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

int pos[2] = {0, 0};
char print[26] = "--------------------------";

int nsleep(long miliseconds)
{
   struct timespec req, rem;

   if(miliseconds > 999)
   {
        req.tv_sec = (int)(miliseconds / 1000);
        req.tv_nsec = (miliseconds - ((long)req.tv_sec * 1000)) * 1000000;
   }
   else
   {
        req.tv_sec = 0;
        req.tv_nsec = miliseconds * 1000000;
   }

   return nanosleep(&req , &rem);
}

void *input()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    int ch = getch();
    switch(ch)
    {
    case KEY_UP:        pos[1]++;
                break;
    case KEY_DOWN:      pos[1]--;
                break;
    case KEY_LEFT:      pos[0]--;
                break;
    case KEY_RIGHT:     pos[0]++;
                break;
    default:
                exit(1);

    }
    return NULL;
}

void *draw()
{
    // int n = (strlen(print) - 1)/2;
    // for (int i = 0, ln = strlen(print); i < ln; i++)
    // {
    //     print[i] = '-';
    // }
    printf("\vx: %i, y: %i\n", pos[0], pos[1]);
    // print[0] = 'x';
    nsleep(34);
    return NULL;
}

int main(void)
{
    while(1)
    {

        pthread_t input_id;
        pthread_t draw_id;
        pthread_create(&draw_id, NULL, draw, NULL);
        pthread_create(&input_id, NULL, input, NULL);
        pthread_join(draw_id, NULL);
        pthread_cancel(input_id);
    }
    return 0;
}
