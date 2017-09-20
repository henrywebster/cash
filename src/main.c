#include "cash.h"
#include <string.h>
#include <stdio.h>

int main(int argv, char * argc[])
{
    char buffer[C$_BUFFER_SIZE];
    char* argbuffer[8];
    memset(argbuffer, '\0', sizeof(char*) * 8);

    ssize_t size = 1;

    int numArgs;

    C$_Prompt();
    while (C$_Getline(buffer, C$_BUFFER_SIZE) > 0)
    {


	numArgs = C$_Parse(buffer, argbuffer, size);
	if(strcmp ("ls", argbuffer[0])==0){
		C$_LS(argbuffer[1]);
	}
	if(strcmp ("cd", argbuffer[0])==0){
		C$_Chdir(argbuffer[1]);	
	}
	
	if(strcmp ("ln", argbuffer[0])==0){
		C$_LN(argbuffer[1], argbuffer[2]);	
	}
	
	if(strcmp ("rm", argbuffer[0])==0){
		C$_RM(argbuffer[1]);
	}
	if(strcmp ("exit", argbuffer[0])==0){
		return 0;	
	}


	/*int i;
	for (i = 0; i < 8; i++)
	{
	    printf("Current arg buffer: %p:\n", argbuffer + i);
	    printf("%p: %s\n", argbuffer[i], argbuffer[i]);
	}*/

	C$_Prompt();
	C$_ClearArgs(argbuffer, numArgs);
    }

    return 0;
}
