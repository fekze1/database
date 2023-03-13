#include "data_base.h"
#include "datagen.h"
#include "cmprtrs.h"
#include "commands.h"
#include "outputs.h"

void command_sort_gen_data(User ***data, unsigned int *data_length)
{
	if (!(*data))
	{
		not_initialized();
		return;
	}

	print_sort_menu();

	char *sort_parameter_str;

	command_input();
	if (!input_str(&sort_parameter_str)) 
	{	
		delete_data(*data, *data_length);	
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
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_id);
		finish_sort = clock();
	break;
	case 2:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_id);
		finish_sort = clock();
	break;
	case 3:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_name);
		finish_sort = clock();
	break;
	case 4:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_name);
		finish_sort = clock();
	break;
	case 5:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_gender);
		finish_sort = clock();
	break;
	case 6:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_gender);
		finish_sort = clock();
	break;
	case 7:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_age);
		finish_sort = clock();
	break;
	case 8:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_age);
		finish_sort = clock();
	break;
	case 9:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_type);
		finish_sort = clock();
	break;
	case 10:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_type);
		finish_sort = clock();
	break;
	default:
		invalid_input_menu();
		return;
	break;
	}
	all_sort = (long double)(finish_sort - start_sort) / CLOCKS_PER_SEC;

	sorted(all_sort);

    time_spent(all_sort);
}

void command_write_data(User ***data, unsigned int *data_length)
{
    if (!(*data))
    {
        not_initialized();
        return;
    }

	FILE *output_file = fopen("DATABASE.txt", "w");
	if (!output_file)
	{
		file_error();
		delete_data(*data, *data_length);
		exit(-1);
	}


	clock_t start_write = clock();
	for (int i = 0; i < *data_length; i++) print_user_in_file(output_file, (*data)[i]);
	clock_t finish_write = clock();

	long double all_write = (long double)(finish_write - start_write) / CLOCKS_PER_SEC;

	fclose(output_file);

	file_write();
    
    time_spent(all_write);
}

void command_print_gen_data(User ***data, unsigned int *data_length)
{
	if (!(*data))
	{
		not_initialized();
		return;
	}
	print_data(*data, *data_length);
}

void command_print_gen_user(User ***data, unsigned int *data_length)
{
	if (!data)
	{
		not_initialized();
		return;
	}

	id_input();
	char *id_print;
	if(!input_str(&id_print))
	{
		delete_data(*data, *data_length);	
		exit(-1);
	}

	while ((unsigned int)atoi(id_print) <= 0)
	{
		id_invalid();
		free(id_print);

		if (!(input_str(&id_print)))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		} 
	}

	unsigned int id_print_ui = (unsigned int)atoi(id_print);
	free(id_print);

	if (!check_user_id_existence(*data, id_print_ui, *data_length))
	{	
		user_nexist();
		return;
	}
	
	system("clear");
	print_user(get_user_by_id(*data, *data_length, id_print_ui));
}

void command_init_gen_data(User ***data, unsigned int *data_length)
{
	int confirm_flag = 1;

	if (*data)
	{	
		char *confirmation;

		warning_existence();
		
		if (!input_str(&confirmation))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		}
		
		while ((strcmp(confirmation, "yes") != 0) && (strcmp(confirmation, "no") != 0))
		{	
			free(confirmation);
			invalid_input();

			if (!input_str(&confirmation))
			{	
				delete_data(*data, *data_length);	
				exit(-1);
			}
		}

		if (strcmp(confirmation, "yes") == 0)
		{
			delete_data(*data, *data_length);
			confirm_flag = 1;
		} 
		else confirm_flag = 0;

		free(confirmation);
	}
	if (confirm_flag == 1)
	{
		char *amount;

		input_amount();

		if (!(input_str(&amount)))
		{
			free(amount);
			delete_data(*data, *data_length);
			exit(-1);
		} 

		while (atoi(amount) <= 0)
		{
			invalid_amount();

			free(amount);

			if (!(input_str(&amount)))
			{
				free(amount);
				delete_data(*data, *data_length);
				exit(-1);
			}
		}

		clock_t start_gen = clock();
		*data = gen_data(atoi(amount));
		clock_t finish_gen = clock();
		
		*data_length = atoi(amount);
		
		long double all_gen = (long double)(finish_gen - start_gen) / CLOCKS_PER_SEC;
		
		free(amount);
		
		initialization();
		time_spent(all_gen);
	}
}

void command_user_add(User ***data, unsigned int *data_length)
{
	if (!(*data)) 
	{
		not_initialized();
		return;
	}
	User *new_user = create_user();
	if (!new_user)
	{
		delete_data(*data, *data_length);	
		exit(-1);
	}
	add_user(data, new_user, data_length);
	
    user_added();
}

void command_user_delete(User ***data, unsigned int *data_length)
{
	if (!(*data))
	{
		not_initialized();
		return;
	} 

	id_input();
	char *id_deletion;
	if(!input_str(&id_deletion))
	{
		delete_data(*data, *data_length);	
		exit(-1);
	}

	while ((unsigned int)atoi(id_deletion) <= 0)
	{
		id_invalid();
		free(id_deletion);

		if (!(input_str(&id_deletion)))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		} 
	}

	unsigned int id_deletion_ui = (unsigned int)atoi(id_deletion);
	free(id_deletion);

	if (!check_user_id_existence(*data, id_deletion_ui, *data_length))
	{	
		user_nexist();
		return;
	}

	delete_user(data, id_deletion_ui, data_length);
	
    user_deleted();
}

void command_data_sort(User ***data, unsigned int *data_length)
{
	if (!(*data))
	{
		not_initialized();
		return;
	}

	print_sort_menu();

	char *sort_parameter_str;

	command_input();
	if (!input_str(&sort_parameter_str)) 
	{	
		delete_data(*data, *data_length);	
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
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_id);
		finish_sort = clock();
	break;
	case 2:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_id);
		finish_sort = clock();
	break;
	case 3:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_name);
		finish_sort = clock();
	break;
	case 4:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_name);
		finish_sort = clock();
	break;
	case 5:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_gender);
		finish_sort = clock();
	break;
	case 6:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_gender);
		finish_sort = clock();
	break;
	case 7:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_age);
		finish_sort = clock();
	break;
	case 8:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_age);
		finish_sort = clock();
	break;
	case 9:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmp_type);
		finish_sort = clock();
	break;
	case 10:
		start_sort = clock();
		qsort(*data, *data_length, sizeof(User *), (int(*) (const void *, const void *)) cmpr_type);
		finish_sort = clock();
	break;
	default:
		invalid_input_menu();
		return;
	break;
	}
	all_sort = (long double)(finish_sort - start_sort) / CLOCKS_PER_SEC;
	sorted(all_sort);
}

void command_user_change(User ***data, unsigned int *data_length)
{
	if (!data)
	{
		not_initialized();
		return;
	}
	
	id_input();
	char *id_change;
	if(!input_str(&id_change))
	{
		delete_data(*data, *data_length);	
		exit(-1);
	}

	while ((unsigned int)atoi(id_change) <= 0)
	{
		id_invalid();
		free(id_change);

		if (!(input_str(&id_change)))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		} 
	}

	unsigned int id_change_ui = (unsigned int)atoi(id_change);
	free(id_change);

	if (!check_user_id_existence(*data, id_change_ui, *data_length))
	{	
		user_nexist();
		return;
	}

	if(!change_user_by_id(*data, *data_length, id_change_ui))
	{
		delete_data(*data, *data_length);
		exit(-1);
	}
	
    user_changed();
}

void command_print_data(User ***data, unsigned int *data_length)
{
	if (!data)
	{
		not_initialized();
		return;
	}

	print_data(*data, *data_length);
}

void command_print_user(User ***data, unsigned int *data_length)
{
	if (!data)
	{
		not_initialized();
		return;
	}

	id_input();
	char *id_print;
	if(!input_str(&id_print))
	{
		delete_data(*data, *data_length);	
		exit(-1);
	}

	while ((unsigned int)atoi(id_print) <= 0)
	{
		id_invalid();
		free(id_print);

		if (!(input_str(&id_print)))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		} 
	}

	unsigned int id_print_ui = (unsigned int)atoi(id_print);
	free(id_print);

	if (!check_user_id_existence(*data, id_print_ui, *data_length))
	{	
		user_nexist();
		return;
	}
	
	print_user(get_user_by_id(*data, *data_length, id_print_ui));
}

void command_init_data(User ***data, unsigned int *data_length)
{
	int confirm_flag = 1;

	if (*data)
	{	
		char *confirmation;

		warning_existence();
		
		if (!input_str(&confirmation))
		{
			delete_data(*data, *data_length);	
			exit(-1);
		}
		
		while ((strcmp(confirmation, "yes") != 0) && (strcmp(confirmation, "no") != 0))
		{	
			free(confirmation);
			
            invalid_input();

			if (!input_str(&confirmation))
			{	
				delete_data(*data, *data_length);	
				exit(-1);
			}
		}

		if (strcmp(confirmation, "yes") == 0)
		{
			delete_data(*data, *data_length);
			confirm_flag = 1;
		} 
		else confirm_flag = 0;

		free(confirmation);
	}
	if (confirm_flag == 1)
	{
		*data = init_data();
		*data_length = 0;
		
        initialization();
	} 
}
