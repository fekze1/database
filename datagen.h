#ifndef DATAGEN_H
#define DATAGEN_H

#include "source.h"

int rand_int_range(int min, int max);

char *gen_name();

unsigned int gen_age();

char gen_gender();

enum user_type gen_type();

User *gen_user();

User **gen_data(unsigned int data_amount);

void delete_rand_data(User **data, unsigned int data_length);

#endif