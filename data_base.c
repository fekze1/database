#include "source.h"
#include "data_base.h"
#include "outputs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

User *get_user_by_id(User **data, unsigned int data_length, unsigned int id)
{
	for (int i = 0; i < data_length; i++) if (data[i]->id == id) return data[i];

	return NULL;
}

User *create_user()
{	
	char *name;
	
	input_name();

	if (!(input_str(&name))) return NULL;

	while (strlen(name) < 3 || strlen(name) > 15)
	{
		invalid_name();

		free(name);

		if (!(input_str(&name))) return NULL;
	}

	char *gender;
	
	input_gender();

	if (!(input_str(&gender)))
	{
		free(name);
		return NULL;
	} 

	while (gender[0] != 'M' && gender[0] != 'F')
	{
		invalid_gender();

		free(gender);

		if (!(input_str(&gender)))
		{
			free(name);
			return NULL;
		} 
	}

	char *age;

	input_age();

	if (!(input_str(&age)))
	{
		free(name);
		free(gender);
		return NULL;
	} 

	while (atoi(age) <= 0)
	{
		invalid_age();

		free(age);

		if (!(input_str(&age)))
		{
			free(name);
			free(gender);
			return NULL;
		} 
	}
	char gender_ch = gender[0];
	unsigned int age_ui = (unsigned int)atoi(age);
	free(gender);
	free(age);
	
	return init_user(name, gender_ch, age_ui, 2);
}

bool change_user_by_id(User **data, unsigned int data_length, unsigned int id)
{
	User *user = get_user_by_id(data, data_length, id);

	print_user(user);

	char *parameter;

	input_parameter();

	if (!(input_str(&parameter)))
	{
		free(parameter);
		return false;
	} 

	while (strcmp(parameter, "name") != 0 && strcmp(parameter, "gender") != 0 && strcmp(parameter, "age") != 0 )
	{
		invalid_parameter();

		free(parameter);

		if (!(input_str(&parameter)))
		{
			free(parameter);
			return false;
		} 
	}

	if (strcmp(parameter, "name") == 0 )
	{
		char *new_name;

		input_name();

		if (!(input_str(&new_name)))
		{
			free(parameter);
			return false;
		} 

		while (strlen(new_name) < 3 || strlen(new_name) > 15)
		{
			invalid_name();

			free(new_name);

			if (!(input_str(&new_name)))
			{
				free(parameter);
				return false;
			} 
		}

		free(user->name);
		user->name = new_name;

		free(parameter);
		return true;
	}
	
	if (strcmp(parameter, "gender") == 0 )
	{
		char *new_gender;

		input_gender();

		if (!(input_str(&new_gender)))
		{
			free(parameter);
			return false;
		} 

		while (new_gender[0] != 'M' && new_gender[0] != 'F')
		{
			invalid_gender();

			free(new_gender);

			if (!(input_str(&new_gender)))
			{
				free(parameter);
				return false;
			} 
		}

		user->gender = new_gender[0];

		free(new_gender);
		free(parameter);
		return true;
	}

	char *new_age;

	input_age();

	if (!(input_str(&new_age)))
	{
		free(parameter);
		return false;
	} 

	while (atoi(new_age) <= 0)
	{
		invalid_age();

		free(new_age);

		if (!(input_str(&new_age)))
		{
			free(parameter);
			return false;
		} 
	}

	user->age = (unsigned int)atoi(new_age);
	
	free(new_age);
	free(parameter);
	return true;
}

bool check_user_existence(User **data, User *user, unsigned int data_length)
{	
	for (int i = 0; i < data_length; i++) if (data[i] == user) return true;
	
	return false;
}

bool check_user_id_existence(User **data, unsigned int id, unsigned int data_length)
{
	for (int i = 0; i < data_length; i++) if (data[i]->id == id) return true;
	
	return false;
}

void add_user(User ***data, User *user, unsigned int *data_length_ptr) 
{
	if (check_user_existence(*data, user, *data_length_ptr))
	{
		user_in_database();
		return;
	}
	
	(*data_length_ptr)++;
	*data = (User **)realloc(*data, *data_length_ptr * sizeof(User *));
	(*data)[*data_length_ptr - 1] = user;
	(*data)[*data_length_ptr - 1]->id = LAST_ID + 1;
	LAST_ID++;
}

void delete_user(User ***data, unsigned int id, unsigned int *data_length_ptr)
{	
	User *user;
	int deleted_ind = 0;

	for (int i = 0; i < *data_length_ptr; i++)
	{
		if ((*data)[i]->id == id)
		{
			user = (*data)[i];
			deleted_ind = i;
		} 
	}

	for (int i = deleted_ind; i < *data_length_ptr - 1; i++)
	{
		(*data)[i] = (*data)[i + 1];
	}

	(*data_length_ptr)--;
	if (*data_length_ptr > 0) *data = (User **)realloc(*data, *data_length_ptr * sizeof(User **));

	free(user->name);
	free(user);
}

User **init_data()
{
	LAST_ID = 0;
	User **data = (User **)calloc(1, sizeof(User *));
	return data;
}

User *init_user(char *name, char gender, unsigned int age, enum user_type type)
{	
	User *user = (User *)calloc(1, sizeof(User));
	user->name = name;
	user->gender = gender;
	user->age = age;
	user->type = type;

	return user;
}

void print_user(User *user)
{
	if (user->id == 0) printf("\n\t\033[91mUSER IS NOT IN DATABASE\033[0m\n");
	else printf("\n\t\033[93mID:\033[0m %u\n", user->id);
	printf("\t\033[93mName:\033[0m %s\n", user->name);
	printf("\t\033[93mGender:\033[0m %c\n", user->gender);
	printf("\t\033[93mAge:\033[0m %u\n", user->age);
	printf("\t\033[93mType:\033[0m %s\n\n", get_type_name(user->type));
}

void print_data(User **data, unsigned int data_length)
{	
	system("clear");
	for (int i = 0; i < data_length; i++) print_user(data[i]);
}

void delete_data(User **data, unsigned int data_length)
{	
	for (int i = 0; i < data_length; i++)
	{
		free(data[i]->name);
		free(data[i]);
	}

	free(data);
	printf("\n");
}

void print_user_in_file(FILE *file, User *user)
{
	fprintf(file, "\nID: %u, NAME: %s, GENDER: %c, AGE: %u, TYPE: %s\n", user->id, user->name, user->gender, user->age, get_type_name(user->type));
}