#ifndef COMMANDS_H
#define COMMANDS_H

#include "source.h"

void command_sort_gen_data(User ***data, unsigned int *data_length);

void command_write_data(User ***data, unsigned int *data_length);

void command_print_gen_data(User ***data, unsigned int *data_length);

void command_print_gen_user(User ***data, unsigned int *data_length);

void command_init_gen_data(User ***data, unsigned int *data_length);

void command_user_add(User ***data, unsigned int *data_length);

void command_user_delete(User ***data, unsigned int *data_length);

void command_user_delete(User ***data, unsigned int *data_length);

void command_data_sort(User ***data, unsigned int *data_length);

void command_user_change(User ***data, unsigned int *data_length);

void command_print_data(User ***data, unsigned int *data_length);

void command_print_user(User ***data, unsigned int *data_length);

void command_init_data(User ***data, unsigned int *data_length);

#endif