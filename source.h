#ifndef SOURCE_H
#define SOURCE_H

#include <stdbool.h>

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

bool change_user_by_id(User ***data, unsigned int id);

void std_mode();

void print_menu();

void print_sort_menu();

char *get_type_name(enum user_type type);

bool check_user_existence(User **data, User *user, unsigned int data_length);

bool check_user_id_existence(User **data, unsigned int id, unsigned int data_length);

void add_user(User ***data, User *user, unsigned int *data_length_ptr);

void delete_user(User ***data, unsigned int id, unsigned int *data_length_ptr);

int find_length(User *data);

User **init_data();

User *init_user(char *name, char gender, unsigned int age, enum user_type type);

void print_user(User *user);

void print_data(User **data, unsigned int data_length);

void delete_data(User **data, unsigned int data_length);

#endif