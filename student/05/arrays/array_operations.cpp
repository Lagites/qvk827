#include "array_operations.hh"
#include <iostream>

int greatest_v1(int *itemptr, int size)
{
    int greatest = INT32_MIN;
    for(int i = 0 ; i < size ; i++){        
        if(*itemptr > greatest)
            greatest = *itemptr;
        itemptr++;
    }

    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = INT32_MIN;
    while(itemptr != endptr){
        if(*itemptr > greatest)
            greatest = *itemptr;
        itemptr++;
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while(itemptr != endptr){
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    while(leftptr < rightptr){
        rightptr--;
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        leftptr++;
    }
}
