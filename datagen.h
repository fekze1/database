#ifndef DATAGEN_H
#define DATAGEN_H

int rand_int_range(int min, int max);

char *gen_name();

unsigned int gen_age();

char gen_gender();

enum user_type gen_type();

#endif