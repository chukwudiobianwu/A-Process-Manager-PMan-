#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "linked_list.h"

Node* head = NULL;

Node* add_newNode(Node* sasuke, pid_t new_pid, char * new_path) {
  sasuke->pid = new_pid;
  sasuke->path = new_path;
  sasuke->next = NULL;
  sasuke->pull= true;
	if (head == NULL) {
		head = sasuke;
	} else {
		Node* fortnite = head;
		while (fortnite->next != NULL) {
			fortnite = fortnite->next;
		}
		fortnite->next = sasuke;
	}
}

Node * deleteNode(pid_t pid){


if (!PifExist(head,pid)){

	printf("Pid does not exist\n");
	}
else{
	Node* slom = head;
	Node* bull = NULL;

	while (slom != NULL) {
		if (slom->pid == pid) {
			if (slom == head) {
				head = head->next;
			} else {
				bull->next = slom->next;
			}
			free(slom);
		}
		bull = slom;
		slom= slom->next;
	}

}
return head;
}

void printList(struct Node *node){
	printf("Path\t Pid\n");
	while (node!= NULL) {
	
	if(node->pull == false){
		printf("%s:\t %d     Paused\n",node->path , node->pid);
	}
	if(node->pull ==true){
		printf("%s:\t %d     Running\n",node->path , node->pid);
		
	}
	node = node->next;
  }
}

int PifExist(Node* node, pid_t pid){
	while (node != NULL) {
		if (node->pid == pid) {
			return true;
		}
		node = node->next;
	}
	return false;


}
