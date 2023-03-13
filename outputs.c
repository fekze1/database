#include "outputs.h"
#include <stdio.h>
#include <stdlib.h>

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
    system("clear");
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

void invalid_enum()
{
    printf("\033[91mINVALID ENUM\033[0m\n");
}

void command_input()
{
    printf("Input command: ");
}

void programm_end()
{
    system("clear");
    printf("\t\t\033[92m   DELETING DATABASE, PROGRAM COMPLETION\033[0m\n");
}

void invalid_input_menu()
{
    system("clear");
    printf("\t\t\t\033[91m      INVALID INPUT\033[0m\n");
}

void not_initialized()
{
    system("clear");
	printf("\t\t\033[91m    YOU DID NOT INITIALIZE ANY DATABASE\033[0m\n");
}

void sorted()
{
    system("clear");
	printf("\t\t\033[92m     DATABASE WAS SUCCESFULLY SORTED\033[0m\n");
}

void file_error()
{
    printf("\033[91mSOME ERROR HAPPENED WHILE OPENING FILE\033[0m");
}

void file_write()
{
    system("clear");
	printf("\t\t\033[92mDATABASE WAS SUCCESSFULLY WRITED TO \"DATABASE.txt\"\033[0m\n");
}

void id_input()
{
    printf("Input user`s ID: ");
}

void id_invalid()
{
    printf("Invalid ID, try again: ");
}

void user_nexist()
{
    system("clear");
	printf("\t\t\033[91m    USER WITH THIS ID DOES NOT EXIST\033[0m\n");
}

void warning_existence()
{
    printf("\t\t\033[91mYOUR CURRENT DATABASE WILL BE DELETED\033[0m\n");
    printf("\t\t\033[91m   YOU WANT TO CONTINUE? (yes/no)\033[0m\n");
    printf("Input: ");
}

void invalid_input()
{
    printf("Invalid input, try again: ");
}

void input_amount()
{
    printf("Input amount of users: ");
}

void initialization()
{
    system("clear");
	printf("\t\t\033[92m   DATABASE WAS SUCCESSFULLY INITIALIZED\033[0m\n");
}

void time_spent(long double time)
{
    printf("\t\t\033[92m          TIME SPENT: %0.7Lf\033[0m\n", time);
}

void user_added()
{
    system("clear");
	printf("\t\t\033[92m       USER WAS SUCCESSFULLY ADDED\033[0m\n");
}

void user_deleted()
{
    system("clear");
	printf("\t\t\033[92m     USER WAS SUCCESSFULLY DELETED\033[0m\n");
}

void user_changed()
{
    system("clear");
	printf("\t\t\033[92m     USER WAS SUCCESSFULLY CHANGED\033[0m\n");
}

void invalid_amount()
{
    printf("Invalid amount, try again: ");
}

void input_name()
{
    printf("Input name: ");
}

void invalid_name()
{
    printf("Invalid name, try again: ");
}

void input_gender()
{
    printf("Choose gender (M/F): ");
}

void invalid_gender()
{
    printf("Invalid gender, try again: ");
}

void input_age()
{
    printf("Input age: ");
}

void invalid_age()
{
    printf("Invalid age, try again: ");
}

void input_parameter()
{
    printf("Parameter to change (name/gender/age): ");
}

void invalid_parameter()
{
    printf("Invalid parameter, try again: ");
}

void user_in_database()
{
    printf("\033[92mUSER IS ALREADY IN THE DATABASE\033[0m\n");
}