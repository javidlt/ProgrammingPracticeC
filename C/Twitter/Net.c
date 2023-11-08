#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_FOLLOWED 5

struct strNode {
    char username[30];
    struct strNode* next;
    Count followCount;
    struct strNode* follows[MAX_FOLLOWED];
};

typedef struct strNode* Node;

typedef unsigned short Count;
typedef enum { False, True } Bool;

struct strNet {
    Node first;
    Count userCount;
    Count followCount;
};

typedef struct strNet* Net;

Net net_create(){
    Net n = (Net) malloc(sizeof(struct strNet));
    n->first = NULL;
    n->followCount = 0;
    n->userCount = 0;
    return n;
}

// Reto 3: función findUser
Node findUser(Net net, char username[]) {
    Node current = net->first;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Reto 4: función net_addUser
Bool net_addUser(Net net, char username[]) {
    if (findUser(net, username) != NULL) {
        return False;
    }

    Node newUser = (Node) malloc(sizeof(struct strNode));

    if (strlen(username) < sizeof(newUser->username)) {
        strcpy(newUser->username, username);
    } 
    else {
        free(newUser);
        return False;
    }

    newUser->followCount = 0;
    for (int i = 0; i < MAX_FOLLOWED; i++) {
        newUser->follows[i] = NULL;
    }
    newUser->next = net->first;
    net->first = newUser;
    net->userCount++;

    return True;
}

// Reto 5: función net_follow
Bool net_follow(Net net, char username[], char username2[]){
    if(strcmp(username, username2) != 0 ||  /*compruebo que los username sean diferentes y que existan*/
        findUser(net, username) != NULL || 
        findUser(net, username2) != NULL
        ) {
        Node userFollow = findUser(net, username);
        Node userFollowed = findUser(net, username2);
        if(userFollow->followCount < MAX_FOLLOWED){
            for (int i = 0; i < userFollow->followCount; i++) {
                if(strcmp(userFollow->follows[i], username2) == 0) {
                    return False;
                }
            }
            userFollow->follows[userFollow->followCount] = userFollowed;
            userFollow->followCount++;

            return True;
        }
        else return False;
    }
    else return False;
}

// Reto 6: función net_Print
void net_print(Net net) {
    Node current = net->first;
    while (current != NULL) {
        printf("User %s follows %d user(s):\n", current->username, current->followCount);
        if (current->followCount > 0) {
            for (int i = 0; i < current->followCount; i++) {
                printf("%d) %s\n", i+1, current->follows[i]->username);
            }
        } 
        else {
            printf("User %s does not follow anyone yet.\n", current->username);
        }
        current = current->next;
    }
}
