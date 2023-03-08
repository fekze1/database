#include "stdio.h"
#include "stdlib.h"
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
			printf("\033[91mwrong enum\033[0m\n");
		break;
	}
	return "WRONG TYPE";
}

int add_user(User **data, User user, int length) 
{
	if (length < 0) printf("\033[91minvalid length\033[0m\n");

	length++;
	*data = (User *)realloc(*data, length * sizeof(User));
	*(data)[length - 1] = user;

	return length;
}

User *init_data()
{
	User *data = (User *)calloc(1, sizeof(User));
	return data;
}

User create_user(char *fullname, char gender, unsigned int age, enum user_type type)
{	
	User user;
	user.fullname = fullname;
	user.gender = gender;
	user.age = age;
	user.type = type;
	return user;
}

void print_user(User user)
{
	printf("----------\n\033[93mName:\033[0m %s\n\033[93mGender:\033[0m %c\n\033[93mAge:\033[0m %u\n\033[93mType:\033[0m %s\n----------\n", user.fullname, user.gender, user.age, get_type_name(user.type));
}

void print_data(User *data)
{
	int i = 0;
	while(data[i].fullname)
	{
		printf("%s", data[i].fullname);
	}
}
