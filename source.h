#ifndef SOURCE_H
#define SOURCE_H

enum user_type
{
    admin = 0,
    moderator,
    common_user,
    banned_user
};

typedef struct
{
    char *fullname;
    char gender;
    unsigned int age;
    enum user_type type;

}User;

char *get_type_name(enum user_type type);

int add_user(User **data, User user, int length);

User *init_data();

User create_user(char *fullname, char gender, unsigned int age, enum user_type type);

void print_user(User user);

void print_data(User *data);

#endif