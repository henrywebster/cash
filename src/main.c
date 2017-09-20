#include "cash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    char buffer[C$_BUFFER_SIZE];
    char * eargv[8];
    char * argbuffer[8];
    memset(argbuffer, '\0', sizeof(char*) * 8);
    memset(eargv, '\0', sizeof(char *) * 8);
    ssize_t size = 1;

    int numArgs;

    C$_Prompt();
    while (C$_Getline(buffer, C$_BUFFER_SIZE) > 0)
    {


	numArgs = C$_Parse(buffer, argbuffer, size);

	int i;
	for (i = 0; i < numArgs; i++)
	{
	    eargv[i] = argbuffer[i];
	}



	short pid;
	if (!(pid = fork()))
	{
	    execv(argbuffer[0], eargv);
	    exit(1);
	}
	else
	{
	    memset(eargv, '\0', sizeof (char *) * numArgs);
	    int rcode;
	    while (pid != wait(&rcode))
		;
	    if (rcode != 0)
	    {
		/* go through built-in commands */

		if (strcmp ("cd", argbuffer[0]) == 0)
		{
		    C$_Chdir(argbuffer[1]);	
		}
		else if (strcmp ("ln", argbuffer[0]) == 0)
		{
		    C$_Link(argbuffer[1], argbuffer[2]);	
		}
		else if (strcmp ("rm", argbuffer[0]) == 0)
		{
		    C$_Remove(argbuffer[1]);
		}
		else if (strcmp ("exit", argbuffer[0]) == 0)
		{
		    return 0;	
		}
		else
		{
		    C$_Putline(STDERR_FILENO, "ca$h ERROR: not a file or builtin command");
		}
	    }
	}

	C$_Prompt();
	C$_Clrbuffs(numArgs, argbuffer, eargv);
    }

    return 0;
}
