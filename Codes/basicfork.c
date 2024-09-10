#include <stdio.h>
#include <unistd.h>
#include<unistd.h>
int main(){
printf("I am proccess %ld\n",(long)getpid());
printf("My parent process is %ld\n",(long)getppid());
printf("*************Before Fork******************\n");
fork();
printf("*************After Fork******************\n");
printf("I am proccess %ld\n",(long)getpid());
printf("My parent process is %ld\n",(long)getppid());
return 0;



}
