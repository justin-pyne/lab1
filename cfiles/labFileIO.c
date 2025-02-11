#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

struct user {
    char username[50];
    char password[256];
    char firstname[50];
    char lastname[50];
    int admin;
};

char* cs621Hash(const char* password) {
    return crypt(password, "00");
}

struct user* createUsers(int* count) {
    FILE *fp = fopen("credential_file", "r");
    if (fp == NULL) { 
        return NULL;
    }
    int lines = 0;
    int currChar;
    while ((currChar = fgetc(fp)) != EOF) {
        if (currChar == '\n'){
            lines++;
        }
    }
    fclose(fp);
    struct user *arr = malloc(sizeof(struct user) * lines);
    if (arr == NULL) {
        return NULL;
    }
    *count = lines;
    return arr;
}

void populateUsers(void* users) {
    struct user *p = (struct user *)users;
    FILE *fp = fopen("credential_file", "r");
    if (fp == NULL) {
        return;
    }
    char line[512];
    int i = 0;
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *token = strtok(line, "\t\n");
            if (token == NULL) {
                continue;
            }
            strcpy((p + i)->firstname, token);
            token = strtok(NULL, "\t\n");
            if (token == NULL) {
                continue;
            }
            strcpy((p + i)->lastname, token);

            token = strtok(NULL, "\t\n");
            if (token == NULL) {
                continue;
            }
            strcpy((p + i)->username, token);

            token = strtok(NULL, "\t\n");
            if (token == NULL) {
                continue;
            }
            strcpy((p + i)->password, token);

            token = strtok(NULL, "\t\n");
            if (token == NULL) {
                continue;
            }
            (p + i)->admin = atoi(token);

            i++;
        }
    fclose(fp);
}

int checkAdminPassword(char* password, struct user* users, int count) {
    for (int i = 0; i < count; ++i) {
        if (strcmp((users + i)->username, "admin") == 0) {
            if (strcmp((users + i)->password, cs621Hash(password)) == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

struct user* addUser(struct user* users, int* count, char* username, char* password, char* firstname, char* lastname, int admin) {
    int new_count = (*count) + 1;
    struct user *new_arr = realloc(users, sizeof(struct user) * new_count);
    if (new_arr == NULL) {
        perror("Failed to realloc");
        return NULL;
    }
    struct user *insert_at = new_arr + (*count);
    strcpy(insert_at->username, username);
    strcpy(insert_at->firstname, firstname);
    strcpy(insert_at->lastname, lastname);
    insert_at->admin = admin;
    char *hashed = cs621Hash(password);
    strcpy(insert_at->password, hashed);
    (*count) = new_count;
    return new_arr;
}

void saveUsers(struct user* users, int count) {
    FILE *fp = fopen("credential_file", "w");
    if (fp == NULL) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\t%s\t%s\t%s\t%d\n",
                (users + i)->firstname,
                (users + i)->lastname,
                (users + i)->username,
                (users + i)->password,
                (users + i)->admin);
    }
    fclose(fp);
}

int main(void) {
    int user_count = 0;
    struct user* users = createUsers(&user_count);
    if (users == NULL) {
        return EXIT_FAILURE;
    }
    populateUsers(users);

    printf("Enter admin password to add new users:");
    char entered_admin_password[50];
    scanf("%s", entered_admin_password);
    if (checkAdminPassword(entered_admin_password, users, user_count)) {
        struct user new_user;
        printf("Enter username:");
        scanf("%s", new_user.username);
        printf("Enter first name:");
        scanf("%s", new_user.firstname);
        printf("Enter last name:");
        scanf("%s", new_user.lastname);
        printf("Enter password:");
        scanf("%s", new_user.password);
        printf("Enter admin level:");
        scanf("%d", &(new_user.admin));
        users = addUser(users, &user_count, new_user.username, new_user.password, new_user.firstname, new_user.lastname, new_user.admin);
        if (users == NULL) {
            return EXIT_FAILURE;
        }
    }
    saveUsers(users, user_count);
    free(users);
    return EXIT_SUCCESS;
}
