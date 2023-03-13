#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "source.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

User *get_user_by_id(User **data, unsigned int data_length, unsigned int id);

User *create_user();

bool change_user_by_id(User **data, unsigned int data_length, unsigned int id);

bool check_user_existence(User **data, User *user, unsigned int data_length);

bool check_user_id_existence(User **data, unsigned int id, unsigned int data_length);

void add_user(User ***data, User *user, unsigned int *data_length_ptr);

void delete_user(User ***data, unsigned int id, unsigned int *data_length_ptr);

User **init_data();

User *init_user(char *name, char gender, unsigned int age, enum user_type type);

void print_user(User *user);

void print_data(User **data, unsigned int data_length);

void delete_data(User **data, unsigned int data_length);

void print_user_in_file(FILE *file, User *user);

#endif