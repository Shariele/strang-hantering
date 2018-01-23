#include <stdio.h>
#include <stdlib.h> //atoi
#include "strang.h"


int main(int argc, char **argv){
	char *buff, *buffReset; 
	int size = 10, buffInt = 0;

	buff = getLine(size);
	buffReset = buff;

	printf("Char input: ");
	while(*buff != '\0')
		printf("%c", *buff++);

	printf("\n");

	buff = buffReset;
	buffInt = atoi(buff);
	if(buffInt == 0)
		printf("Invalid number\n");
	else
		printf("As an int: %d\n", buffInt);


	return 0;
}
