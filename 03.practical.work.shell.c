#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main() {


printf("Main before fork()\n");
	int pid = fork();
	char command[256], arguments[256];
	if (pid == 0) {

		printf("Enter your command: ");
		scanf("%s", command);

		if(strcmp(command,"quit") == 0){
			return 0;
		}

		
		printf("Enter your arguments: " );
		scanf("%s", arguments);
		if(strcmp(command,"quit") == 0){
			return 0;
		}

		printf("I am child after fork(), launching %s %s\n", command, arguments);
		char *args[]= { command, arguments , NULL};
		execvp(command, args);
		printf("Finished launching %s %s\n", command, arguments);
	}
	else {
		printf("I am parent after fork(), child is %d\n", pid);
		wait(0);
	}
	return 0;
}