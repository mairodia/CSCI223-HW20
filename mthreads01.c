// =================================================================================
// File: mthreads01.c (Spring 2018)
// =================================================================================
// Programmer: Jennifer King
// Date: 5/14/2018
// Project: Posix Threads
// Professor: Scott Edwards
// Class: CSCI 223 F | TR 4:30PM
// Description:
//      Takes as input two int arguments which repreasents the speed at which the
//      primary and secondary threads should print.
// =================================================================================

#define _BSD_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *ThreadFunc(void *vptr);

int main(int argc, char* argv[])
{
    auto        int             intOne;
    auto        int             intTwo;

    if(3 != argc)
    {
        puts("Usage: ./a.out <#primary microseconds> <#secondary microseconds>");
        exit(EXIT_FAILURE);
    }

    sscanf(argv[1], "%d", &intOne);
    sscanf(argv[2], "%d", &intTwo);

    unsigned long primary;
    unsigned long secondary;

    primary = intOne;
    secondary = intTwo;

    pthread_t tid;
    pthread_create(&tid, NULL, ThreadFunc, &secondary);
    int index = 0;

    for(;; index ++)
    {
        printf("Primary thread at %lu microseconds, counter = %d\n", primary, index);
        usleep(primary);
       // pthread_join(tid, NULL);
    }

    return 0;
}

void *ThreadFunc(void *vptr)
{
    unsigned long seconds = *((unsigned long *)vptr);
    static int index;

    for(; ; index ++)
    {
        printf("Secondary thread at %lu microseconds, counter = %d\n", seconds, index);
        usleep(seconds);
    }

}
