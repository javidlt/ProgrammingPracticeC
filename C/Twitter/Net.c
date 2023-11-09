#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_FOLLOWED 5

typedef unsigned short Count;

struct strNode {
    char username[30];
    struct strNode* next;
    Count followCount;
    struct strNode* follows[MAX_FOLLOWED];
};

typedef struct strNode* Node;

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

void printUserInfo(Node user) {
    if (user != NULL) {
        printf("Username: %s\n", user->username);
        // Imprimir otras propiedades del nodo si las hay
    } else {
        printf("El nodo es NULL\n");
    }
}

// Reto 5: función net_follow
Bool net_follow(Net net, char username[], char username2[]){
     /*compruebo que los username sean diferentes y que existan*/
    if(strcmp(username, username2) != 0 && findUser(net, username) != NULL && findUser(net, username2) != NULL) {
        Node userFollow = findUser(net, username);
        Node userFollowed = findUser(net, username2);
        if(userFollow->followCount < MAX_FOLLOWED){
            for (int i = 0; i < userFollow->followCount; i++) {
                if(strcmp(userFollow->follows[i]->username, username2) == 0) {
                    return False;
                }
            }
            userFollow->follows[userFollow->followCount] = userFollowed;
            userFollow->followCount++;
            return True;

        }
        else return False;
    } else {
        return False;
    }
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

void net_unfollowAll(Net net, Node userToUnfollow) {
    if (userToUnfollow != NULL) {
        Node current = net->first;

        while (current != NULL) {
            // Verificar si el usuario actual sigue al usuario que queremos hacer unfollow
            for (int i = 0; i < current->followCount; i++) {
                if (strcmp(current->follows[i]->username, userToUnfollow->username) == 1) {
                    // Eliminar el follow
                    for (int j = i; j < current->followCount - 1; j++) {
                        current->follows[j] = current->follows[j + 1];
                    }
                    current->followCount--;
                    // se hace break porque no se puede seguir más de una vez a un mismo usuario
                    break; 
                }
            }
            current = current->next;
        }
    }
}


Bool net_delUser(Net net, char username[]) {
    // En caso de que exista el usuario
    Node NodeToSearch = findUser(net, username);
    if (NodeToSearch != NULL){
        Node current = net->first;
        // Buscar nodo anterior para que podamos corregir el orden de la lista
        while (strcmp(current->next->username,username) == 1){
            printUserInfo(current);
            current = current->next;
        }
        // Conectamos el nodo anterior al que se va a borrar con su posterior
        current->next = NodeToSearch->next;
        // Buscar si el nodo a borrar es seguido por otros usuarios
        net_unfollowAll(net, NodeToSearch);
        // hacemos el free del nodo  a borrar 
        free(NodeToSearch);
        return True;
    }
    return False;
}


int main() {
    Net myNet = net_create();

    // Agregamos algunos usuarios
    net_addUser(myNet, "user1");
    net_addUser(myNet, "user2");
    net_addUser(myNet, "user3");

    // Intentamos agregar un usuario existente (esto debería devolver False)
    if (net_addUser(myNet, "user1")) {
        printf("Error: El usuario ya existe.\n");
    }

    // Imprimimos la red después de agregar usuarios
    printf("Red despues de agregar usuarios:\n");
    net_print(myNet);

    // Intentamos seguir a usuarios
    net_follow(myNet, "user1", "user2");
    net_follow(myNet, "user1", "user3");
    net_follow(myNet, "user2", "user3");

    // // Intentamos seguir a un usuario que no existe (esto debería devolver False)
    if (net_follow(myNet, "user4", "user1") == 0) {
        printf("Error: El usuario user4 no existe.\n");
    }

    // Imprimimos la red después de seguir a usuarios
    printf("\nRed despues de seguir a usuarios:\n");
    net_print(myNet);

    // Eliminamos un usuario
    net_delUser(myNet, "user2");

    // Intentamos eliminar un usuario que no existe (esto debería devolver False)
    if (!net_delUser(myNet, "user4")) {
        printf("Error: El usuario user4 no existe.\n");
    }

    // Imprimimos la red después de eliminar usuarios
    printf("\nRed después de eliminar usuarios:\n");
    net_print(myNet);

    // Liberamos la memoria de la red
    free(myNet);

    return 0;
}
