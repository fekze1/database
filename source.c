#include "source.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *input_str() 
{
	char *string = (char *)malloc(1);
	char buffer[81];
	int n, str_length = 0;
	*string = '\0';
	
	do
	{
		n = scanf("%80[^\n]", buffer);
		
		if(n < 0)
		{
			free(string);
			string = NULL;
			continue;
		}

		if(n == 0) scanf("%*c");

		else 
		{
			str_length += strlen(buffer);
			string = (char *)realloc(string, str_length + 1);
			string = strcat(string, buffer);
		}	
	} while(n > 0);
	
	return string;
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
			printf("\033[91mINVALID ENUM\033[0m\n");
		break;
	}
	return "WRONG TYPE";
}

void gen_mode()
{

}

bool command_check(char *command_str)
{
	if ((strcmp(command_str, "1") != 0) && (strcmp(command_str, "2") != 0) && (strcmp(command_str, "3") != 0) && (strcmp(command_str, "4") != 0) && (strcmp(command_str, "5") != 0) && (strcmp(command_str, "6") != 0) && (strcmp(command_str, "7") != 0) && (strcmp(command_str, "8") != 0))
	{
		return false;
	}

	return true;
}

void std_mode()
{	
	unsigned int data_length = 0;
	User **data = NULL;
	short int command = 0;
	char *command_str;

	while(command != 8)
	{	
		print_menu();
		printf("Input command: ");

		command_str = input_str();
		if (!command_str) 
		{	
			free(data);
			printf("\n");
			exit(-1);
		}

		while (command_check(command_str) == false)
		{
			printf("\033[91mInvalid input, try again: \033[0m");
			free(command_str);
			command_str = input_str();

			if (!command_str)
			{
				free(data);
				printf("\n");
				exit(-1);
			}
		}
		
		command = atoi(command_str);
		free(command_str);

		switch (command)
		{
			case 1:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");

				else
				{
				}
			break;

			case 2:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
			break;

			case 3:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
			break;

			case 4:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
			break;

			case 5:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
			break;


			case 6:
				if (!data) printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
			break;

			case 7:
				int confirm_flag = 1;

				if (data)
				{	
					char *confirmation;
					printf("\t\t\033[91mYOUR CURRENT DATABASE WILL BE DELETED\033[0m\n");
					printf("\t\t\033[91m   YOU WANT TO CONTINUE? (yes/no)\033[0m\n");
					
					printf("Input: ");
					confirmation = input_str();
					if (!confirmation)
					{
						free(data);
						printf("\n");
						exit(-1);
					}
					
					while ((strcmp(confirmation, "yes") != 0) && (strcmp(confirmation, "no") != 0))
					{	
						free(confirmation);
						printf("Invalid input, try again: ");
						confirmation = input_str();
						if (!confirmation)
						{	

							free(data);
							printf("\n");
							exit(-1);
						}
					}

					if (strcmp(confirmation, "yes") == 0)
					{
						delete_data(data, data_length);
						confirm_flag = 1;
					} 
					else confirm_flag = 0;

					free(confirmation);
				}
				if (confirm_flag == 1) data = init_data();
			break;

			case 8:
				exit(0);
			break;

			default:
				printf("\033[91mInvalid input, try again\033[0m");
			break;
		}
	}
	delete_data(data, data_length);	
}

void print_menu()
{
	printf("\n\t\t\t\033[40m\033[92m     LIST OF COMMANDS     \033[0m\n");
	printf("\t\t\t\033[40m\033[92m1. ADD USER               \033[0m\n");
	printf("\t\t\t\033[40m\033[92m2. DELETE USER            \033[0m\n");
	printf("\t\t\t\033[40m\033[92m3. SORT DATABASE          \033[0m\n");
	printf("\t\t\t\033[40m\033[92m4. CHANGE USER            \033[0m\n");
	printf("\t\t\t\033[40m\033[92m5. PRINT DATA             \033[0m\n");
	printf("\t\t\t\033[40m\033[92m6. PRINT USER             \033[0m\n");
	printf("\t\t\t\033[40m\033[92m7. (RE)INITIALIZE DATABASE\033[0m\n");
	printf("\t\t\t\033[40m\033[92m8. EXIT                   \033[0m\n");
}

bool check_user_existence(User **data, User *user, unsigned int data_length)
{	
	for (int i = 0; i < data_length; i++) if (data[i] == user) return true;
	
	return false;
}

void add_user(User ***data, User *user, unsigned int *data_length_ptr) 
{
	//(*)
	if (check_user_existence(*data, user, *data_length_ptr))
	{
		printf("\033[92mUSER IS ALREADY IN THE DATABASE\033[0m\n");
		return;
	}

	(*data_length_ptr)++;
	*data = (User **)realloc(*data, *data_length_ptr * sizeof(User *));
	(*data)[*data_length_ptr - 1] = user;
	(*data)[*data_length_ptr - 1]->id = *data_length_ptr;
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
	*data = (User **)realloc(*data, *data_length_ptr * sizeof(User **));

	free(user->name);
	free(user);
}

User **init_data()
{
	User **data = (User **)calloc(1, sizeof(User *));
	return data;
}

User *init_user(char *name, char gender, unsigned int age, enum user_type type)
{	
	//Сделать проверку на вводимые данные (*)
	User *user = (User *)calloc(1, sizeof(User));
	user->name = name;
	user->gender = gender;
	user->age = age;
	user->type = type;

	return user;
}

void print_user(User *user)
{
	// (*)
	if (user->id == 0) printf("\n\t\033[91mUSER IS NOT IN DATABASE\033[0m\n");
	else printf("\n\t\033[93mID:\033[0m %u\n", user->id);
	printf("\t\033[93mName:\033[0m %s\n", user->name);
	printf("\t\033[93mGender:\033[0m %c\n", user->gender);
	printf("\t\033[93mAge:\033[0m %u\n", user->age);
	printf("\t\033[93mType:\033[0m %s\n\n", get_type_name(user->type));
}

void print_data(User **data, unsigned int data_length)
{	
	// (*)
	for (int i = 0; i < data_length; i++) print_user(data[i]);
}

void delete_data(User **data, unsigned int data_length)
{	
	for (int i = 0; i < data_length; i++)
	{
		free(data[i]);
	}

	free(data);
}
