#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int childpid = 0;

void handler(int signal_num){
	printf("Signal %d => ", signal_num);
	switch (signal_num) {
	case SIGTSTP:
		printf("pause\n"); 
		if (childpid) kill(childpid,SIGTSTP);
		break;
	case SIGINT:
	case SIGTERM:
		printf("Terminated\n");
		exit(0);
		break;
	}
}


int main() {
signal(SIGTSTP, handler);
signal(SIGINT, handler);
signal(SIGTERM, handler);

while(1){
	printf("customShell: ");
	int pid = fork();
	char command[256];
	if (pid == 0) {

		fgets(command,sizeof(command),stdin);

                if(strcmp(command,"/q\n") == 0){
                        return 0;
                }

		int pid = fork();
		if(pid){
			childpid = pid;
			waitpid(pid,NULL,0);
		}else{
			char *args[]= {"/bin/bash", "-c",command,NULL};
			execvp("/bin/bash", args);
		}
	}
	else {
		
		wait(0);
	}
}
	return 0;
}
