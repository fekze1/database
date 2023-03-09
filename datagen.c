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

User *gen_user()
{
    return init_user(gen_name(), gen_gender(), gen_age(), gen_type());
}

User **gen_data(unsigned int data_amount)
{   
    //(*)

    User **rand_data = (User **)calloc(data_amount, sizeof(User *));

    for (int i = 0; i < data_amount; i++)
    {
        rand_data[i] = gen_user();
        rand_data[i]->id = i + 1;
    }

    return rand_data;
}

void delete_rand_data(User **data, unsigned int data_length)
{
    for (int i = 0; i < data_length; i++)
    {
        free(data[i]->name);
        free(data[i]);
    }

    free(data);
}
