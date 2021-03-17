#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>

int childpid;
int i_thread = 2;
char cmd[1000];

void handler(int signal_num){
    printf("Signal %d => ", signal_num);
    switch(signal_num){
        case SIGTSTP:
            printf("Pause\n");
            kill(childpid, SIGTSTP);
            break;
        case SIGINT:
        case SIGTERM:
            printf("Terminated\n");
            exit(0);
            break;
    }
}

void* do_thread(){
    // detect if we have a write redirection >

    int pid = fork();
    if(pid){
        childpid = pid;
        waitpid(pid,NULL,0);
    }else{
        char *args[]= {"/bin/bash", "-c",cmd,NULL};
        execvp("/bin/bash", args);
    }

    pthread_exit(&i_thread);

}

int main(void) {
    signal(SIGTSTP, handler);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);


    while (1) {
        printf("USShell> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (strcmp(cmd, "/q\n") == 0) break;

        pthread_t id;
        pthread_create(&id, NULL, do_thread, NULL);
        pthread_join(id, NULL);


    }
    printf("end of shell");
    return 0;
}














