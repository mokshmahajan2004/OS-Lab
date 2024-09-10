#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
int main(void)
{
int pid;
int status;
printf("Hello World\n");
pid=fork();
if (pid==-1){
perror ("Fork Failed");
exit(1);
}
if (pid==0){
printf("I am the child process=%d\n",getpid());
}
else{
wait(&status);/*Parent wait for child to finish*/
//printf("Child process with pid =%d completed with a status %d\n",pid,status);
printf("I am parent process=%d\n",getpid());
return 0;
}
}
