#include "source.h"

int main()
{
    unsigned int data_length = 0;
    unsigned int *data_length_ptr = &data_length;

    User *test = init_user("Test", 'M', 18, 0);
    User **data = init_data();
    
    data = add_user(data, test, &data_length);
    data = add_user(data, test, &data_length);
    data = add_user(data, test, &data_length);

    print_data(data, data_length);

    delete_data(data, data_length);
    return 0;
}