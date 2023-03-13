#include "source.h"
#include "datagen.h"
#include "data_base.h"
#include "cmprtrs.h"
#include "commands.h"
#include "outputs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

bool input_str(char **string) 
{
	*string = (char *)malloc(1);
	char buffer[81];
	int n, str_length = 0;
	**string = '\0';
	
	do
	{
		n = scanf("%80[^\n]", buffer);
		
		if(n < 0)
		{
			free(*string);
			*string = NULL;
			continue;
		}

		if(n == 0) scanf("%*c");

		else 
		{
			str_length += strlen(buffer);
			*string = (char *)realloc(*string, str_length + 1);
			*string = strcat(*string, buffer);
		}	
	} while(n > 0);

	if (!(*string)) return false;
	
	return true;
}

char *get_type_name(enum user_type type)
{
	switch (type)
	{
		case 0:
			return "ADMIN";
		break;
		case 1:
			return "MODERATOR";
		break;
		case 2:
			return "USER";
		break;
		case 3:
			return "BANNED";
		break;
		default:
			invalid_enum();
		break;
	}
	return "WRONG TYPE";
}

void gen_mode()
{
	unsigned int data_length = 0;
	User **data = NULL;
	short int command = 0;
	char *command_str;

	while(command != 6)
	{	
		print_gen_menu();
		command_input();

		if (!input_str(&command_str)) 
		{	
			delete_data(data, data_length);	
			exit(-1);
		}
		
		command = atoi(command_str);
		free(command_str);

		switch (command)
		{
			case 1:
				command_sort_gen_data(&data, &data_length);
			break;

			case 2:
				command_write_data(&data, &data_length);
			break;

			case 3:
				command_print_gen_data(&data, &data_length);
			break;
			case 4:
				command_print_gen_user(&data, &data_length);
			break;

			case 5:
				command_init_gen_data(&data, &data_length);
			break;
			case 6:
				programm_end();
			break;
			default:
				invalid_input_menu();
			break;
		}
	}

	delete_data(data, data_length);	

	exit(0);
}

void std_mode()
{	
	unsigned int data_length = 0;
	User **data = NULL;
	short int command = 0;
	char *command_str;

	while(command != 8)
	{	
		print_std_menu();
		command_input();

		if (!input_str(&command_str)) 
		{	
			delete_data(data, data_length);	
			exit(-1);
		}
		
		command = atoi(command_str);
		free(command_str);

		switch (command)
		{
			case 1:
				command_user_add(&data, &data_length);
			break;

			case 2:
				command_user_delete(&data, &data_length);
			break;

			case 3:
				command_data_sort(&data, &data_length);
			break;
			case 4:
				command_user_change(&data, &data_length);
			break;

			case 5:
				command_print_data(&data, &data_length);
			break;
			case 6:
				command_print_user(&data, &data_length);
			break;

			case 7:
				command_init_data(&data, &data_length);
			break;

			case 8:
				programm_end();
			break;

			default:
				invalid_input_menu();
			break;
		}
	}

	delete_data(data, data_length);	
}