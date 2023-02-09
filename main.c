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
  sasuke->path =malloc(sizeof(char) * 100);
  strcpy(sasuke->path , new_path);
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

void look(char* blue, char** tir) {
	FILE *kl = fopen(blue, "r");
	char orange[1000];
	if (kl != NULL) {
		int h = 0;
		while (fgets(orange, sizeof(orange)-1, kl) != NULL) {
			char* ed;
			ed = strtok(orange, " ");
			tir[h] = ed;
			while (ed != NULL) {
				tir[h] = ed;
				ed = strtok(NULL, " ");
				h++;
			}
		}
		fclose(kl);
	} else {
		printf("Could not check the status of the File\n");
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

}

Node* Retn(pid_t pid) {
	Node* boom = head;
if (boom != NULL){
	while (boom!= NULL) {
		if (boom->pid == pid) {
			return boom;
		}
		boom = boom->next;
	}
}
}


void func_BG(char **cmd){
  Node* sasuke= (Node*)malloc(sizeof(Node));
  pid_t pid = fork();
	if (pid == 0) {  
		execvp(cmd[1], &cmd[1]);
		printf("Could not compute command %s\n", cmd[1]);
		exit(1);
	}else if (pid > 0){	
		printf("Path has begun %d\n", pid);
		add_newNode(sasuke, pid, cmd[1]);
		sleep(1);
	} else {
		printf("Could not Fork,Please try again\n");
	}
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

void func_BGlist(){
printList(head);

}


void func_BGkill(char * str_pid){
  int x;
  sscanf(str_pid, "%d", &x);
if (!PifExist(head,x)) {
		printf("Error: Process %s does not exist.\n",str_pid);
	}
else{
  kill(x,SIGTERM);
  printf("Terminating pid\n");
  checkb();
}
}


void func_BGstop(char * str_pid){
  int x;
  sscanf(str_pid, "%d", &x);
if (!PifExist(head,x)) {
		printf("Error: Process %s does not exist.\n",str_pid);
	}
else{
  kill(x,SIGSTOP);
  printf("Stopping pid\n");
  		Node *big = Retn(x);
		big->pull = false;
	printf("Path %d was paused.\n", x);
	}
}


void func_BGstart(char * str_pid){
  int x;
  sscanf(str_pid, "%d", &x);
if (!PifExist(head,x)) {
	printf("Error: Process %s does not exist.\n",str_pid);
	}
else{
  kill(x,SIGCONT);
  printf("pid Starting\n");
	Node *big = Retn(x);
	big->pull = true;
	printf("Path %d was started.\n", x);
}
}


void checkb() {
	int	check;
	pid_t pid;
		pid = waitpid(-1, &check,WCONTINUED | WNOHANG | WUNTRACED);
		if (waitpid(pid, &check,WUNTRACED) == -1 ) {
			if (WIFEXITED(check)) {
				printf("Path %d terminated.\n", pid);
				deleteNode(pid);
			}
			else if (WIFSIGNALED(check)) {
				printf("Background process %d was killed.\n", pid);
				deleteNode(pid);
			}
			else{
				sleep(1);
			}

}
}

void func_pstat(char * x){
  int str_pid;
  sscanf(x, "%d", &str_pid);

  if(!PifExist(head,str_pid)){

		printf("Error: Process %d does not exist.\n", str_pid);

	}
else {
		char path1[130];
		char path2[130];
		char* drin[130];
		char* gb;
		char prop[128][128];	
		char* lib = prop[39];
		char* yan = prop[40];
		long unsigned int utime;
		long unsigned int stime;
		sprintf(path1, "/proc/%d/stat", str_pid);
		sprintf(path2, "/proc/%d/status", str_pid);
		look(path1, drin);
		FILE* F = fopen(path2, "r");
		if (F = NULL) {
			int c = 0;
			while (fgets(prop[c], 128, F) != NULL) {
				c++;
			}
			fclose(F);
		} else {
			printf("Could not read the status of the file\n");
		}
		
		utime= strtoul(prop[13], &gb, 10) / sysconf(_SC_CLK_TCK);
		stime= strtoul(prop[14], &gb, 10) / sysconf(_SC_CLK_TCK);
		printf("Here are the Stats\n");
		printf("comm:\t%s\n", drin[1]);
		printf("state:\t%s\n", drin[2]);
		printf("utime:\t%lu\n", utime);
		printf("stime:\t%lu\n", stime);
		printf("rss:\t%s\n", drin[24]);
		printf("voluntary switches:%s\n", lib);
		printf("Non voluntary switches:%s\n", yan);
	} 
}

int main(){
    char user_input_str[50];
    while (true) {
      printf("Pman: > ");
      fgets(user_input_str, 50, stdin);
      printf("User input: %s \n", user_input_str);
      char * ptr = strtok(user_input_str, " \n");
      if(ptr == NULL){
        continue;
      }
      char * lst[50];
      int index = 0;
      lst[index] = ptr;
      index++;
      while(ptr != NULL){
        ptr = strtok(NULL, " \n");
        lst[index]=ptr;
        index++;
      }
      if (strcmp("bg",lst[0]) == 0){
        func_BG(lst);
      } else if (strcmp("bglist",lst[0]) == 0) {
        func_BGlist(lst);
      } else if (strcmp("bgkill",lst[0]) == 0) {
        func_BGkill(lst[1]);
      } else if (strcmp("bgstop",lst[0]) == 0) {
        func_BGstop(lst[1]);
      } else if (strcmp("bgstart",lst[0]) == 0) {
        func_BGstart(lst[1]);
      } else if (strcmp("pstat",lst[0]) == 0) {
        func_pstat(lst[1]);
      } else if (strcmp("q",lst[0]) == 0) {
        printf("Bye Bye \n");
        exit(0);
      } else {
        printf("Invalid input\n");
      }
    }

  return 0;
}

