#include "source.h"
#include "datagen.h"
#include "data_base.h"
#include "cmprtrs.h"

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