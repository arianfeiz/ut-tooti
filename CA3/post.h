#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct post{ // user id nevisande poste 
    user* user_id;
    int id;
    int like_num;
    char* post_txt;
    struct post* next;
} post;


//make post instance and add it to posts linked list
post* add_post(char* _post_txt, user* _user_id, int _id, post* first_post){
    post* new_post = (post*)malloc(sizeof(post));
    new_post->post_txt = _post_txt;
    new_post->user_id = _user_id;
    new_post->id = _id;
    new_post->like_num = 0;
    if(first_post == NULL)
        return new_post;
    post* tmp = first_post;
    while(tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_post;
    _user_id->post_num++;
}
