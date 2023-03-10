#include "source.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int get_int_from_stdin(int max_symbols)
{
	//(*)
    char users_amount_tmp[10];
    unsigned int users_amount;
    fgets(users_amount_tmp, 10, stdin);
    users_amount = atoi(users_amount_tmp);
}


void gen_mode()
{
    printf("Input amount of users: ");
    unsigned int users_amount = (unsigned int)get_int_from_stdin(10);
}

void std_mode()
{	
	unsigned int data_length = 0;
	User **data = NULL;
	short int command = 0;
	while(command != 8)
	{	
		print_menu();
		printf("Input command: ");
		scanf("%hd", &command);

		switch (command)
		{
			case 1:
			break;

			case 2:
				printf("Input ID: ");
				unsigned int id = (unsigned int)get_int_from_stdin(10);
				delete_user(data, id, &data_length);
			break;

			case 3:
			break;

			case 4:
			break;

			case 5:
			break;

			case 6:
			break;

			case 7:
				int confirm_flag = 1;

				if (data)
				{	
					char confirmation;
					printf("\t\t\033[91mYOUR CURRENT DATABASE WILL BE DELETED\033[0m\n");
					printf("\t\t\033[91mYOU WANT TO CONTINUE? (y/n)\033[0m\n");
					
					printf("Input: ");
					getchar();
					confirmation = getchar();

					while (confirmation != 'y' && confirmation != 'n')
					{	
						printf("Invalid input, try again: ");
						confirmation = getchar();
					}

					if (confirmation == 'y')
					{
						delete_data(data, data_length);
						confirm_flag = 1;
					} 
					else confirm_flag = 0;
				}
				if (confirm_flag == 1) data = init_data();
			break;

			case 8:
			break;

			default:
				printf("\nInvalid input, try again TESTEST\n");
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

User **add_user(User **data, User *user, unsigned int *data_length_ptr) 
{
	//(*)
	if (check_user_existence(data, user, *data_length_ptr))
	{
		printf("\033[92mUSER IS ALREADY IN THE DATABASE\033[0m\n");
		return data;
	}

	(*data_length_ptr)++;
	data = (User **)realloc(data, *data_length_ptr * sizeof(User *));
	data[*data_length_ptr - 1] = user;
	data[*data_length_ptr - 1]->id = *data_length_ptr;

	return data;
}

User **delete_user(User **data, unsigned int id, unsigned int *data_length_ptr)
{	
	User *user;
	int deleted_ind = 0;

	for (int i = 0; i < *data_length_ptr; i++)
	{
		if (data[i]->id == id)
		{
			user = data[i];
			deleted_ind = i;
		} 
	}

	for (int i = deleted_ind; i < *data_length_ptr - 1; i++)
	{
		data[i] = data[i + 1];
	}

	(*data_length_ptr)--;
	data = (User **)realloc(data, *data_length_ptr * sizeof(User **));

	free(user);
	return data;
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
