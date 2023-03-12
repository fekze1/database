#include "source.h"
#include "datagen.h"
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

User *get_user_by_id(User **data, unsigned int data_length, unsigned int id)
{
	for (int i = 0; i < data_length; i++) if (data[i]->id == id) return data[i];

	return NULL;
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

User *create_user()
{	
	char *name;
	printf("Input name: ");

	if (!(input_str(&name))) return NULL;

	while (strlen(name) < 3 || strlen(name) > 15)
	{
		printf("Invalid name, try again: ");
		free(name);

		if (!(input_str(&name))) return NULL;
	}

	char *gender;
	printf("Choose gender (M/F): ");

	if (!(input_str(&gender)))
	{
		free(name);
		return NULL;
	} 

	while (gender[0] != 'M' && gender[0] != 'F')
	{
		printf("Invalid gender, try again: ");
		free(gender);

		if (!(input_str(&gender)))
		{
			free(name);
			return NULL;
		} 
	}

	char *age;
	printf("Input age: ");
	if (!(input_str(&age)))
	{
		free(name);
		free(gender);
		return NULL;
	} 

	while (atoi(age) <= 0)
	{
		printf("Invalid age, try again: ");
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
	printf("Parameter to change (name/gender/age): ");
	if (!(input_str(&parameter)))
	{
		free(parameter);
		return false;
	} 

	while (strcmp(parameter, "name") != 0 && strcmp(parameter, "gender") != 0 && strcmp(parameter, "age") != 0 )
	{
		printf("Invalid parameter, try again: ");
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
		printf("Input new name: ");

		if (!(input_str(&new_name)))
		{
			free(parameter);
			return false;
		} 

		while (strlen(new_name) < 3 || strlen(new_name) > 15)
		{
			printf("Invalid name, try again: ");
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
		printf("Choose new gender (M/F): ");

		if (!(input_str(&new_gender)))
		{
			free(parameter);
			return false;
		} 

		while (new_gender[0] != 'M' && new_gender[0] != 'F')
		{
			printf("Invalid gender, try again: ");
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
	printf("Input new age: ");
	if (!(input_str(&new_age)))
	{
		free(parameter);
		return false;
	} 

	while (atoi(new_age) <= 0)
	{
		printf("Invalid age, try again: ");
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

int cmp_id(User **first_user,User **second_user)
{	
	return ((User *)(*first_user))->id - ((User *)(*second_user))->id;
}

int cmpr_id(User **first_user,User **second_user)
{	
	return -1 * (((User *)(*first_user))->id - ((User *)(*second_user))->id);
}

int cmp_name(User **first_user,User **second_user)
{	
	return strcmp(((User *)(*first_user))->name, ((User *)(*second_user))->name);
}

int cmpr_name(User **first_user,User **second_user)
{	
	return -1 * strcmp(((User *)(*first_user))->name, ((User *)(*second_user))->name);
}

int cmp_gender(User **first_user,User **second_user)
{	
	return -1 * ((((User *)(*first_user))->gender - ((User *)(*second_user))->gender));
}

int cmpr_gender(User **first_user,User **second_user)
{	
	return (((User *)(*first_user))->gender - ((User *)(*second_user))->gender);
}

int cmp_age(User **first_user,User **second_user)
{	
	return ((User *)(*first_user))->age - ((User *)(*second_user))->age;
}

int cmpr_age(User **first_user,User **second_user)
{	
	return -1 * (((User *)(*first_user))->age - ((User *)(*second_user))->age);
}

int cmp_type(User **first_user,User **second_user)
{	
	return ((User *)(*first_user))->type - ((User *)(*second_user))->type;
}

int cmpr_type(User **first_user,User **second_user)
{	
	return -1 * (((User *)(*first_user))->type - ((User *)(*second_user))->type);
}

void print_user_in_file(FILE *file, User *user)
{
	fprintf(file, "\nID: %u, NAME: %s, GENDER: %c, AGE: %u, TYPE: %s\n", user->id, user->name, user->gender, user->age, get_type_name(user->type));
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
		printf("Input command: ");

		if (!input_str(&command_str)) 
		{	
			delete_data(data, data_length);	
			printf("\n");
			exit(-1);
		}
		
		command = atoi(command_str);
		free(command_str);

		switch (command)
		{
			case 1:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}

				system("clear");
				print_sort_menu();

				char *sort_parameter_str;

				printf("Input command: ");
				if (!input_str(&sort_parameter_str)) 
				{	
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}
				
				int sort_parameter = atoi(sort_parameter_str);
				free(sort_parameter_str);
				
				clock_t start_sort;
				clock_t finish_sort;
				long double all_sort;

				switch (sort_parameter)
				{
				case 1:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_id);
					finish_sort = clock();
				break;
				case 2:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_id);
					finish_sort = clock();
				break;
				case 3:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_name);
					finish_sort = clock();
				break;
				case 4:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_name);
					finish_sort = clock();
				break;
				case 5:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_gender);
					finish_sort = clock();
				break;
				case 6:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_gender);
					finish_sort = clock();
				break;
				case 7:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_age);
					finish_sort = clock();
				break;
				case 8:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_age);
					finish_sort = clock();
				break;
				case 9:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_type);
					finish_sort = clock();
				break;
				case 10:
					start_sort = clock();
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_type);
					finish_sort = clock();
				break;
				default:
					system("clear");
					printf("\t\t\t\033[91m      INVALID INPUT\033[0m\n");
				break;
				}
				all_sort = (long double)(finish_sort - start_sort) / CLOCKS_PER_SEC;
				system("clear");
				printf("\t\t\033[92m     DATABASE WAS SUCCESFULLY SORTED\033[0m\n");
				printf("\t\t\033[92m      TIME SPENT: %.7Lf seconds\033[0m\n", all_sort);
			break;

			case 2:
				FILE *output_file = fopen("DATABASE.txt", "w");
				if (!output_file)
				{
					printf("\033[91mSOME ERROR HAPPENED WHILE OPENING FILE\033[0m");
					delete_data(data, data_length);
					printf("/n");
					exit(-1);
				}


				clock_t start_write = clock();
				for (int i = 0; i < data_length; i++) print_user_in_file(output_file, data[i]);
				clock_t finish_write = clock();

				long double all_write = (long double)(finish_write - start_write) / CLOCKS_PER_SEC;

				fclose(output_file);

				system("clear");
				printf("\t\t\033[92mDATABASE WAS SUCCESSFULLY WRITED TO \"DATABASE.txt\"\033[0m\n");
				printf("\t\t\033[92m              TIME SPENT: %0.7Lf\033[0m\n", all_write);
			break;

			case 3:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}
				system("clear");
				print_data(data, data_length);
			break;
			case 4:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}

				printf("Input user`s ID: ");
				char *id_print;
				if(!input_str(&id_print))
				{
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}

				while ((unsigned int)atoi(id_print) <= 0)
				{
					printf("Invalid ID, try again: ");
					free(id_print);

					if (!(input_str(&id_print)))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					} 
				}

				unsigned int id_print_ui = (unsigned int)atoi(id_print);
				free(id_print);

				if (!check_user_id_existence(data, id_print_ui, data_length))
				{	
					system("clear");
					printf("\t\t\033[91m    USER WITH THIS ID DOES NOT EXIST\033[0m\n");
					break;
				}
				
				system("clear");
				print_user(get_user_by_id(data, data_length, id_print_ui));
			break;

			case 5:
				int confirm_flag = 1;

				if (data)
				{	
					char *confirmation;
					printf("\t\t\033[91mYOUR CURRENT DATABASE WILL BE DELETED\033[0m\n");
					printf("\t\t\033[91m   YOU WANT TO CONTINUE? (yes/no)\033[0m\n");
					
					printf("Input: ");
					
					if (!input_str(&confirmation))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					}
					
					while ((strcmp(confirmation, "yes") != 0) && (strcmp(confirmation, "no") != 0))
					{	
						free(confirmation);
						printf("Invalid input, try again: ");

						if (!input_str(&confirmation))
						{	
							delete_data(data, data_length);	
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
				if (confirm_flag == 1)
				{
					char *amount;
					printf("Input amount of users: ");
					if (!(input_str(&amount)))
					{
						free(amount);
						delete_data(data, data_length);
						exit(-1);
					} 

					while (atoi(amount) <= 0)
					{
						printf("Invalid amount, try again: ");
						free(amount);

						if (!(input_str(&amount)))
						{
							free(amount);
							delete_data(data, data_length);
							exit(-1);
						} 
					}

					clock_t start_gen = clock();
					data = gen_data(atoi(amount));
					clock_t finish_gen = clock();
					
					data_length = atoi(amount);
					
					long double all_gen = (long double)(finish_gen - start_gen) / CLOCKS_PER_SEC;
					
					free(amount);
					system("clear");
					printf("\t\t\033[92m   DATABASE WAS SUCCESSFULLY INITIALIZED\033[0m\n");
					printf("\t\t\033[92m            TIME SPENT: %0.7Lf\033[0m\n", all_gen);
				}
			break;
			case 6:
				system("clear");
				printf("\t\t\033[92m   DELETING DATABASE, PROGRAM COMPLETION\033[0m\n");
			break;
			default:
				system("clear");
				printf("\t\t\t\033[91m      INVALID INPUT\033[0m\n");
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
		printf("Input command: ");

		if (!input_str(&command_str)) 
		{	
			delete_data(data, data_length);	
			printf("\n");
			exit(-1);
		}
		
		command = atoi(command_str);
		free(command_str);

		switch (command)
		{
			case 1:
				if (!data) 
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}
				User *new_user = create_user();
				if (!new_user)
				{
					delete_data(data, data_length);	
					exit(-1);
				}
				add_user(&data, new_user, &data_length);
				system("clear");
				printf("\t\t\033[92m       USER WAS SUCCESSFULLY ADDED\033[0m\n");
			break;

			case 2:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				} 

				printf("Input user`s ID: ");
				char *id_deletion;
				if(!input_str(&id_deletion))
				{
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}

				while ((unsigned int)atoi(id_deletion) <= 0)
				{
					printf("Invalid ID, try again: ");
					free(id_deletion);

					if (!(input_str(&id_deletion)))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					} 
				}

				unsigned int id_deletion_ui = (unsigned int)atoi(id_deletion);
				free(id_deletion);

				if (!check_user_id_existence(data, id_deletion_ui, data_length))
				{	
					system("clear");
					printf("\t\t\033[91m    USER WITH THIS ID DOES NOT EXIST\033[0m\n");
					break;
				}

				delete_user(&data, id_deletion_ui, &data_length);
				system("clear");
				printf("\t\t\033[92m     USER WAS SUCCESSFULLY DELETED\033[0m\n");
			break;

			case 3:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}

				system("clear");
				print_sort_menu();

				char *sort_parameter_str;

				printf("Input command: ");
				if (!input_str(&sort_parameter_str)) 
				{	
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}
				
				int sort_parameter = atoi(sort_parameter_str);
				free(sort_parameter_str);
				
				switch (sort_parameter)
				{
				case 1:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_id);
				break;
				case 2:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_id);;
				break;
				case 3:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_name);
				break;
				case 4:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_name);
				break;
				case 5:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_gender);
				break;
				case 6:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_gender);
				break;
				case 7:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_age);
				break;
				case 8:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_age);
				break;
				case 9:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_type);
				break;
				case 10:
					qsort(data, data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_type);
				break;
				default:
					system("clear");
					printf("\t\t\t\033[91m      INVALID INPUT\033[0m\n");
				break;
				}
				system("clear");
				printf("\t\t\033[92m     DATABASE WAS SUCCESFULLY SORTED\033[0m\n");
			break;
			case 4:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}
				
				printf("Input user`s ID: ");
				char *id_change;
				if(!input_str(&id_change))
				{
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}

				while ((unsigned int)atoi(id_change) <= 0)
				{
					printf("Invalid ID, try again: ");
					free(id_change);

					if (!(input_str(&id_change)))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					} 
				}

				unsigned int id_change_ui = (unsigned int)atoi(id_change);
				free(id_change);

				if (!check_user_id_existence(data, id_change_ui, data_length))
				{	
					system("clear");
					printf("\t\t\033[91m    USER WITH THIS ID DOES NOT EXIST\033[0m\n");
					break;
				}

				if(!change_user_by_id(data, data_length, id_change_ui))
				{
					delete_data(data, data_length);
					printf("\n");
					exit(-1);
				}
				system("clear");
				printf("\t\t\033[92m     USER WAS SUCCESSFULLY CHANGED\033[0m\n");
			break;

			case 5:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}
				system("clear");
				print_data(data, data_length);
			break;


			case 6:
				if (!data)
				{
					system("clear");
					printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
					break;
				}

				printf("Input user`s ID: ");
				char *id_print;
				if(!input_str(&id_print))
				{
					delete_data(data, data_length);	
					printf("\n");
					exit(-1);
				}

				while ((unsigned int)atoi(id_print) <= 0)
				{
					printf("Invalid ID, try again: ");
					free(id_print);

					if (!(input_str(&id_print)))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					} 
				}

				unsigned int id_print_ui = (unsigned int)atoi(id_print);
				free(id_print);

				if (!check_user_id_existence(data, id_print_ui, data_length))
				{	
					system("clear");
					printf("\t\t\033[91m    USER WITH THIS ID DOES NOT EXIST\033[0m\n");
					break;
				}
				
				system("clear");
				print_user(get_user_by_id(data, data_length, id_print_ui));
			break;

			case 7:
				int confirm_flag = 1;

				if (data)
				{	
					char *confirmation;
					printf("\t\t\033[91mYOUR CURRENT DATABASE WILL BE DELETED\033[0m\n");
					printf("\t\t\033[91m   YOU WANT TO CONTINUE? (yes/no)\033[0m\n");
					
					printf("Input: ");
					
					if (!input_str(&confirmation))
					{
						delete_data(data, data_length);	
						printf("\n");
						exit(-1);
					}
					
					while ((strcmp(confirmation, "yes") != 0) && (strcmp(confirmation, "no") != 0))
					{	
						free(confirmation);
						printf("Invalid input, try again: ");

						if (!input_str(&confirmation))
						{	
							delete_data(data, data_length);	
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
				if (confirm_flag == 1)
				{
					data = init_data();
					data_length = 0;
					system("clear");
					printf("\t\t\033[92m   DATABASE WAS SUCCESSFULLY INITIALIZED\033[0m\n");
				} 
			break;

			case 8:
				system("clear");
				printf("\t\t\033[92m   DELETING DATABASE, PROGRAM COMPLETION\033[0m\n");
			break;

			default:
				system("clear");
				printf("\t\t\t\033[91m      INVALID INPUT\033[0m\n");
			break;
		}
	}

	delete_data(data, data_length);	
}

void print_std_menu()
{
	printf("\n\t\t\t\033[40m\033[92m     LIST OF COMMANDS     \033[0m\n");
	printf("\t\t\t\033[40m\033[92m1. ADD USER               \033[0m\n");
	printf("\t\t\t\033[40m\033[92m2. DELETE USER            \033[0m\n");
	printf("\t\t\t\033[40m\033[92m3. SORT DATABASE          \033[0m\n");
	printf("\t\t\t\033[40m\033[92m4. CHANGE USER            \033[0m\n");
	printf("\t\t\t\033[40m\033[92m5. PRINT DATABASE         \033[0m\n");
	printf("\t\t\t\033[40m\033[92m6. PRINT USER             \033[0m\n");
	printf("\t\t\t\033[40m\033[92m7. (RE)INITIALIZE DATABASE\033[0m\n");
	printf("\t\t\t\033[40m\033[92m8. EXIT                   \033[0m\n");
}

void print_gen_menu()
{
	printf("\n\t\t\t\033[40m\033[92m     LIST OF COMMANDS    \033[0m\n");
	printf("\t\t\t\033[40m\033[92m1. SORT DATABASE         \033[0m\n");
	printf("\t\t\t\033[40m\033[92m2. PRINT DATABASE IN FILE\033[0m\n");
	printf("\t\t\t\033[40m\033[92m3. PRINT DATABASE        \033[0m\n");
	printf("\t\t\t\033[40m\033[92m4. PRINT USER            \033[0m\n");
	printf("\t\t\t\033[40m\033[92m5. (RE)GENERATE DATABASE \033[0m\n");
	printf("\t\t\t\033[40m\033[92m6. EXIT                  \033[0m\n");
}

void print_sort_menu()
{
	printf("\n\t\t    \033[40m\033[92m         LIST OF COMMANDS         \033[0m\n");
	printf("\t\t    \033[40m\033[92m1. SORT BY ID (MIN -> MAX)        \033[0m\n");
	printf("\t\t    \033[40m\033[92m2. SORT BY ID (MAX -> MIN)        \033[0m\n");
	printf("\t\t    \033[40m\033[92m3. SORT BY NAME (A -> Z)          \033[0m\n");
	printf("\t\t    \033[40m\033[92m4. SORT BY NAME (Z -> A)          \033[0m\n");
	printf("\t\t    \033[40m\033[92m5. SORT BY GENDER (MALE -> FEMALE)\033[0m\n");
	printf("\t\t    \033[40m\033[92m6. SORT BY GENDER (FEMALE -> MALE)\033[0m\n");
	printf("\t\t    \033[40m\033[92m7. SORT BY AGE (MIN -> MAX)       \033[0m\n");
	printf("\t\t    \033[40m\033[92m8. SORT BY AGE (MAX -> MIN)       \033[0m\n");
	printf("\t\t    \033[40m\033[92m9. SORT BY TYPE (ADMIN -> BANNED) \033[0m\n");
	printf("\t\t    \033[40m\033[92m10. SORT BY TYPE (BANNED -> ADMIN)\033[0m\n");
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
	//(*)
	if (check_user_existence(*data, user, *data_length_ptr))
	{
		printf("\033[92mUSER IS ALREADY IN THE DATABASE\033[0m\n");
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
	if (*data)
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
}