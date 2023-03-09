#include "source.h"

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
	printf("\t\033[93mType:\033[0m %u\n\n", user->type);
}

void print_data(User **data, unsigned int data_length)
{	
	// (*)
	for (int i = 0; i < data_length; i++) print_user(data[i]);
}

void delete_data(User **data, unsigned int data_length)
{	
	if (data_length == 0) printf("\033[91mINVAlID DATA LENGTH\033[0m\n");

	free(data[0]);
	free(data);
	// for (int i = 0; i < data_length; i++) free(data[i]);
	// free(data);
}
