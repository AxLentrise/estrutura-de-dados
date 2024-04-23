//
// Created by diogo on 27/03/2024.
//
#include <stdio.h>

int main(int argc, char **argv)
{
    // checks if an argument has passed or if more than one
    // expects a path for a txt, csv or any readable file
    // code 450 will be my code for args error
    printf("test");
    if((argc < 1) || (argc > 2)) return 450;

    FILE *fptr;

    if((fptr = fopen(argv[1], "r")) == NULL)
    {
        printf("Error opening file.\n");
        return 400;
    }



    return 99;
}