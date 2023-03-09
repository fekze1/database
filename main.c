#include "source.h"
#include "datagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{
    unsigned int length = 1000;
    User **data = gen_data(length);
    print_data(data, length);

    delete_rand_data(data, length);
}