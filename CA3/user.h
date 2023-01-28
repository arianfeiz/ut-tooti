#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
    char* name;
    char* pass;
    int id;
    int post_num;
    struct user* next;
} user;

//make user instance and add it to users linked list
user* add_user(char* _name, char* _pass, int _id, user* first_user){ // add user sign up mikone 
    user* new_user = (user*)malloc(sizeof(user));
    new_user->name = _name;
    new_user->pass = _pass;
    new_user->id = _id;
    new_user->post_num = 0;
    if(first_user == NULL)
        return new_user;
    user* tmp = first_user;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_user;
}
