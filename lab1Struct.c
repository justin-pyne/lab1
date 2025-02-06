#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct user{
    char username[50];
    char password[50];
    int admin;
};

struct user* createUsers(int max_number_of_users) {
    struct user *arr = malloc(sizeof(struct user) * max_number_of_users);
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}

void initUsers(void* users, int max_number_of_users) {
    struct user *p = (struct user *)users;
    for (int i = 0; i < max_number_of_users; i++) {
        strcpy((p + i)->username, "default");
        strcpy((p + i)->password, "default");
        (p + i)->admin = 0;
    }
}

void addUser1(struct user* users, char* username, char* password,
    int admin, int* count) {
    strcpy((users + *count)->username, username);
    strcpy((users + *count)->password, password);
    (users + *count)->admin, admin;
    (*count)++;
}

void addUser2(struct user* users, struct user* newUser, int* count) {
    //Your code goes here
}

void printUser(struct user* users, int number_of_users) {
    //Your code goes here
}

int main(void) {
    struct user* users = createUsers(10);
    if(users == NULL) {
        return 0;
    }
    int userCount = 0;
    initUsers(users, 10);
    addUser1(users, "admin", "s#1Pa5", 1, &userCount);
    addUser1(users, "vahab", "fgH!12", 0, &userCount);

    struct user u1;
    u1.admin = 2;
    strcpy(u1.username, "usf");
    strcpy(u1.password, "gA24?m");
    addUser2(users, u1, &userCount);
    printUser(users, userCount);
    free(users);
    return 0;
}
