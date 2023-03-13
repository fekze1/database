#ifndef SOURCE_H
#define SOURCE_H

#include <stdbool.h>
#include <stdio.h>

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

static unsigned int LAST_ID;

bool input_str(char **string);

void gen_mode();

User *create_user();

int cmp_id(User **first_user,User **second_user);

int cmpr_id(User **first_user,User **second_user);

int cmp_name(User **first_user,User **second_user);

int cmpr_name(User **first_user,User **second_user);

int cmp_gender(User **first_user,User **second_user);

int cmpr_gender(User **first_user,User **second_user);

int cmp_age(User **first_user,User **second_user);

int cmpr_age(User **first_user,User **second_user);

int cmp_type(User **first_user,User **second_user);

int cmpr_type(User **first_user,User **second_user);

void print_user_in_file(FILE *file, User *user);

void std_mode();

void print_std_menu();

void print_gen_menu();

void print_sort_menu();

char *get_type_name(enum user_type type);

#endif