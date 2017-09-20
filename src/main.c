#include "cash.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    char buffer[C$_BUFFER_SIZE];
    char * eargv[C$_MAX_ARGS];
    char * argbuffer[C$_MAX_ARGS];

    char * infile = 0;
    char * outfile = 0;

    memset(argbuffer, '\0', sizeof(char*) * C$_MAX_ARGS);
    memset(eargv, '\0', sizeof(char *) * C$_MAX_ARGS);
    ssize_t size = 0;
    // ssize

    int numArgs;
    enum rflag flag = WAIT;
    enum rmode mode = QUASH;

    C$_Prompt();
    while (1)
    {
	size = 0;
	flag = WAIT;
	while (flag != DONE)
	{
	    size += (C$_Getline(buffer, C$_BUFFER_SIZE, size, &flag));
	}
	if (size == 0)
	{
	    break;
	}
	
	if ((numArgs = C$_Parse(buffer, argbuffer, size, &infile, &outfile, &mode)) == -1)
	{
	    C$_Putline(STDERR_FILENO, "ca$h ERROR: Redirection error");
	}
	else
	{


	short pid;
	if (!(pid = fork()))
	{

	    int i;
	    for (i = 0; argbuffer[i]; i++)
		eargv[i] = argbuffer[i];

	    // there is something in the in redirect but it can't open: abort
	    if ((infile || outfile) && C$_Redirect(infile, outfile, mode))
		exit(0);
	    else
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
		if (size == 1)
		{
		    // user just pressed enter, ignore
		}
		/* go through built-in commands */
		else if (strcmp ("cd", argbuffer[0]) == 0)
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
	}
	free(infile);
	infile = 0;

	free(outfile);
	outfile = 0;

    	C$_Clrbuffs(C$_MAX_ARGS, argbuffer, eargv);
	C$_Prompt();
	}
    C$_Putline(STDOUT_FILENO, "");
    

    return 0;
}
