#ifndef SOURCE_H
#define SOURCE_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

enum user_type
{
    admin = 0,
    moderator,
    common_user,
    banned_user
};

typedef struct
{
    unsigned int id;
    char *name;
    char gender;
    unsigned int age;
    enum user_type type;

}User;

char *get_type_name(enum user_type type);

bool check_user_existence(User **data, User *user, unsigned int data_length);

User **add_user(User **data, User *user, unsigned int *data_length_ptr);

int find_length(User *data);

User **init_data();

User *init_user(char *name, char gender, unsigned int age, enum user_type type);

void print_user(User *user);

void print_data(User **data, unsigned int data_length);

void delete_data(User **data, unsigned int data_length);

#endif