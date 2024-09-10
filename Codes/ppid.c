#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
printf("I am process %ld\n",(long)getpid());
printf("I am process %ld\n",(long)getppid());
while(1){}
}
