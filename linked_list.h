#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct Node Node;

struct Node{
    pid_t pid;
    char * path;
    Node * next;
    int pull;
};


Node* add_newNode(Node* sasuke, pid_t new_pid, char * new_path);
Node* deleteNode(pid_t pid);
void printList(struct Node *node);
int PifExist(Node *node, pid_t pid);
void checkb();



#endif