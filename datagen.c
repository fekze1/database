#include "source.h"
#include "datagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int rand_int_range(int min, int max)
{   
    //(*)
    srand(clock());
    return (min + rand()%(max - min + 1));
}

char *gen_name()
{   
    int name_length = rand_int_range(5, 15);
    char *rand_name = (char *)calloc(name_length, sizeof(char));

    for (int i = 0; i < name_length - 1; i++)
    {
        rand_name[i] = rand_int_range(33, 126);
    }

    return rand_name;
}

unsigned int gen_age()
{
    return (unsigned int)rand_int_range(1, 100);
}

char gen_gender()
{
    if (rand_int_range(0, 1)) return 'M';
    return 'F';
}

enum user_type gen_type()
{
    return rand_int_range(0, 3);
}
