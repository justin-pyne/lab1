#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

struct new_user {
    char username[50];
    char password[50];
    bool write;
    bool read;
    bool execute;
};

typedef unsigned char bitmap8;

struct user {
    char username[50];
    char password[50];
    bitmap8 permissions;
};

void compare() {
    printf("The size of new_user is %d.\n", sizeof(struct new_user));
    printf("The size of user is %d.\n", sizeof(struct user));
}

void grantPermission(int bitIndex, struct user* user) {
    user->permissions |= (1 << bitIndex);
}

void revokePermission(int bitIndex, struct user* user) {
    user->permissions &= ~(1 << bitIndex);
}

int checkPermission(int bitIndex, struct user* user) {
    if ((user->permissions & (1 << bitIndex)) != 0) {
        return 1;
    } else {
        return 0;
    }
}

void printPermissions(struct user* user) {
    if(checkPermission(0, user)) {
        printf("%s has write permission.\n", user->username);
    }
    else {
        printf("%s doesn't have write permission.\n", user->username);
    }
    if(checkPermission(1, user)) {
        printf("%s has read permission.\n", user->username);
    }
    else {
        printf("%s doesn't have read permission.\n", user->username);
    }
    if(checkPermission(2, user)) {
        printf("%s has execute permission.\n", user->username);
    }
    else {
        printf("%s doesn't have execute permission.\n", user->username);
    }
}

void setPermissions(int new_permissions, struct user* user) {
    user->permissions = 0;
    if (new_permissions & 4) {
        user->permissions |= (1 << 1);
    }
    if (new_permissions & 2) {
        user->permissions |= (1 << 0);
    }
    if (new_permissions & 1) {
        user->permissions |= (1 << 2); 
    }
}

int main(void) {
    struct user user;
    strcpy(user.username, "admin");
    strcpy(user.password, "s#1Pa5");
    user.permissions = 0;
    grantPermission(0, &user);
    grantPermission(1, &user);
    printPermissions(&user);
    revokePermission(1, &user);
    grantPermission(2, &user);
    printPermissions(&user);
    return EXIT_SUCCESS;
}
