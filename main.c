#include "stdio.h"
#include "stdlib.h"
#include "source.h"

int main()
{
    int length = 0;
    User *data = init_data();
    User tmp = create_user("Roman", 'M', 18, admin);
    User tmp1 = create_user("Roman1", 'F', 19, moderator);

    print_user(tmp);
    print_user(tmp1);

    length = add_user(&data, tmp, length);
    
    free(data);
    return 0;
}
