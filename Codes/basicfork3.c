#include <stdio.h>
#include <stdlib.h>
int main(){
	if (fork()&&fork())
		fork();
	printf("1 ");
	return 0;
	
}
