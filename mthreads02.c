// =================================================================================
// File: mthreads02.c (Spring 2018)
// =================================================================================
// Programmer: Jennifer King
// Date: 5/14/2018
// Project: Posix Threads
// Professor: Scott Edwards
// Class: CSCI 223 F | TR 4:30PM
// Description:
//      Takes as input any number of int arguments which repreasents the speed and
//      quantity at which threads should print.
// =================================================================================

#define _BSD_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//struct for passing thread info
typedef struct
{
    int number;
    unsigned long seconds;
    int index;
}Thread;

//function prototype
void *ThreadFunc(void *vptr);

//begin main
int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        puts("Usage: ./a.out <#primary microseconds> <thread #1 microseconds> <thread #2 microsecon$
        exit(EXIT_FAILURE);
    }

    int counter;
    int intOne;
    int result;

    //recieve values for primary thread and check if valid
    result = sscanf(argv[1], "%d", &intOne);
    if(!result)
    {
        puts("Argument 1 is not valid.");
        exit(EXIT_FAILURE);
    }

    //convert to unsigned long
    unsigned long primary = intOne;

    //if there are more threads
    int numThreads = (argc - 2);
    Thread threads[numThreads];
    int temp;

    for(counter = 2; counter < argc; counter++)
    {
        //retrieve input and check if valid
        result = sscanf(argv[counter], "%d", &temp);
        if(!result)
        {
            printf("Argument %d is not valid.\n", counter);
            exit(EXIT_FAILURE);
        }

        //initialize struct members
        threads[counter].number = counter;
        threads[counter].seconds = temp;
        threads[counter].index = 0;

        //create thread
        pthread_t tid;
        pthread_create(&tid, NULL, ThreadFunc, &threads[counter]);
    }

    //begin primary thread loop
    int index = 0;
    for(;; index ++)
    {
        printf("Primary thread at %lu microseconds, counter = %d\n", primary, index);
        usleep(primary);
    }

    return 0;
}//end of main

void *ThreadFunc(void *vptr)
{
    Thread current = *((Thread *)vptr);
    unsigned long seconds = current.seconds;
    int index = current.index;
    int number = current.number;

    for(; ; index ++)
    {
        printf("Secondary thread #%d at %lu microseconds, counter = %d\n", number, seconds, index);
        usleep(seconds);
    }

}//end of ThreadFunc

