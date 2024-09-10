#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
int main(void){
	char *binaryPath="/bin/bash";
	char *arg1="-c";
	char *arg2="echo Visit $HOSTNAME from your browser.";
	char *const env[]={"HOSTNAME=www.thapar.edu",NULL};
	execle(binaryPath,binaryPath,arg1,arg2,NULL,env);
	return 0;
}