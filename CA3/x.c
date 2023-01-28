#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "post.h"


int main(){
    int post_id = 0;
    int user_id = 0;
    
    user* first_user = NULL;
    post* first_post = NULL;
    first_user = add_user("admin", "123456", -1, first_user);
    first_post = add_post("welcome to UT tooti", first_user, -1, first_post);
    
    user* logged = first_user;
    printf("%s logged successful!\n", first_user->name);
    printf("%s\n", first_post->post_txt);


    while(1){
        char command[50];
        scanf("%s", &command);
        //signup user
        if(!strcmp(command, "signup")){
            char name[100];
            char pass[100];
            scanf("%s", &name);
            scanf("%s", &pass);
            add_user(&name[0], &pass[0], user_id++, first_user);
            printf("user with name %s added successfuly!\n", name);
        }

        //search all users if we found user that match with our
        //username and password make that logged user
        else if(!strcmp(command, "login")){
            if(logged != NULL){
                printf("user %s is logged!\n", logged->name);
                continue;
            }
            char name[100];
            char password[100];
            scanf("%s", &name);
            scanf("%s", &password);
            user* tmp = first_user;
            while(1){
                if(tmp == NULL)
                    break;
                if(!strcmp(name, tmp->name) && !strcmp(password, tmp->pass)){
                    logged = tmp;
                    printf("%s logged successfuly!\n", logged->name);
                    break;
                }
                else
                    tmp = tmp->next;
            }
        }

        //get post text from user by std input and added to linked list
        //put the last chat from \n to \0 cause save part will be messed
        //if last char of text be \n
        else if(!strcmp(command, "post")){
            char tmp;
            scanf("%c", &tmp);
            if(logged == NULL){
                printf("nobody logged!\n");
                continue;
            }
            char* text = malloc(sizeof(char) * 1000);
            fgets(text, 1000, stdin);
            printf("%s", text);
            text[strlen(text) - 1] = '\0';
            add_post(text, logged, post_id++, first_post);
            printf("post added successfuly!\n");
        }

        //take post id by std input and search it if
        //the post found increase the like num
        else if(!strcmp(command, "like")){
            char name[100];
            int id;
            scanf("%s", &name);
            scanf("%d", &id);
            post* tmp = first_post;
            int f = 0;
            while(1){
                if(tmp == NULL)
                    break;
                if(tmp->id == id){
                    f = 1;
                    tmp->like_num++;
                    printf("post liked!\n");
                    break;
                }
                tmp = tmp->next;
            }
            if(f == 0){
                printf("post not found!\n");
            }
        }

        //DONE
        else if(!strcmp(command, "logout")){
            if(logged != NULL){
                printf("user %s logged out successfuly!\n", logged->name);
                logged = NULL;
            }
            else{
                printf("no user fined as logged\n");
            }
        }

        //this part will delete post by id
        //for example if we wanna delete node n in all posts we
        //follow below flow but if we wanna delete the first or last node
        //it's different if we want delete last node had to make null previous node
        //and de-allocate the node and if we want to delete first node put next node
        //as first post and de-allocate the node
        /*
        post[n-1] ------> post[n] ------> post[n+1]
        
        TO

        post[n-1] ---/--> post[n] ---/--> post[n+1]
            |                                |
            l--------------------------------l
        
        */
        else if(!strcmp(command, "delete")){
            int id;
            scanf("%d", &id);
            post* x = first_post;
            post* pre = NULL;
            int f = 1;
            while(1){
                if(x == NULL)
                    break;
                if(x->user_id == logged && x->id == id){
                    pre->next = x->next;
                    free(x);
                    printf("post with id %d deleted!\n");
                    f = 2;
                    break;
                }
                if(!(x->user_id == logged) && x->id == id){
                    f = 0;
                }
                pre = x;
                x = x->next;
            }
            if(f == 0)
                printf("no permission to delete\n");
            if(f == 2)
                printf("no post find with id %d\n", id);
        }

        //if no one logged nothing can be search
        //show info of logged user and search all posts and show related post
        //and info to logged usser
        else if(!strcmp(command, "info")){
            if(logged == NULL){
                printf("no user are logged!\n");
                continue;
            }
            printf("username: %s\npass: %s\n", logged->name, logged->pass);
            post* x = first_post;
            while(1){
                if(x == NULL)
                    break;
                if(x->user_id == logged){
                    printf("\ntext of post: %s\n", x->post_txt);
                    printf("post_id : %d\n", x->id);
                    printf("post %d times liked\n", x->like_num);
                }
                x = x->next;
            }
        }

        //this part search all users to find username by std input
        //after find user scan all posts and show related info as
        //previous part "info"
        else if(!strcmp(command, "find_user")){
            char name[100];
            scanf("%s", &name);
            user* tmp = first_user;
            while(1){
                if(tmp == NULL)
                    break;
                if(!strcmp(name, tmp->name)){
                    break;
                }
                else
                    tmp = tmp->next;
            }
            if(tmp == NULL){
                printf("no user fined with name %s\n");
                continue;
            }
            post* x = first_post;
            while(1){
                if(x == NULL)
                    break;
                if(x->user_id == tmp){
                    printf("\npost_id : %d\n", x->id);
                    printf("post %d times liked\n", x->like_num);
                    printf("text of post: %s\n", x->post_txt);
                }
                x = x->next;
            }
            printf("all the post of user %s successfuly searched!\n", tmp->name);
        }

        //this part save all users in text file nearby this code and save it
        FILE* file = fopen("accounts.txt", "w");
        user* tmp = first_user;
        while(tmp!=NULL){
            fwrite(tmp->name, sizeof(char), strlen(tmp->name), file);
            fwrite(" ", 1, 1, file);
            fwrite(tmp->pass, sizeof(char), strlen(tmp->pass), file);
            fwrite(" ", 1, 1, file);
            char itos[10];
            sprintf(itos, "%d", tmp->post_num);
            fwrite(&itos[0], sizeof(char), strlen(itos), file);
            fwrite("\n", 1, 1, file);
            tmp = tmp->next;
        }
        fclose(file);

        //this part save all post in text file nearby this code and save it
        FILE* file1 = fopen("posts.txt", "w");
        post* tmp1 = first_post;
        while(tmp1 != NULL){
            fwrite(tmp1->post_txt, sizeof(char), strlen(tmp1->post_txt), file1);
            fwrite(" ", 1, 1, file1);
            fwrite(tmp1->user_id->name, sizeof(char), strlen(tmp1->user_id->name), file1);
            fwrite(" ", 1, 1, file1);
            char itos[10];
            sprintf(itos, "%d", tmp1->like_num);
            fwrite(&itos[0], sizeof(char), strlen(itos), file1);
            fwrite("\n", 1, 1, file1);
            tmp1 = tmp1->next;
        }
        fclose(file1);
    }
}