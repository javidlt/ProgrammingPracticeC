#include <stdlib.h>
#include <stdio.h>
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