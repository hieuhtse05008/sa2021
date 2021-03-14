#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signal_num) {
printf("Signal %d => ", signal_num);
switch (signal_num) {
case SIGTSTP:
printf("pause\n"); break;
case SIGINT:
case SIGTERM:
printf("Terminated\n");
exit(0);
break;
}
}
int main(void) {
// ctrl z
signal(SIGTSTP, handler);
// ctrl c or killed
signal(SIGINT, handler);
signal(SIGTERM, handler);
while (1) {
sleep(1);
printf(".\n");
}
printf("end");
return 0;
}
