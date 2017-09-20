#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


#include "cash.h"

const char * C$_PROMPT_TEXT = "ca$h> ";
const char * NEW_LINE = "\n";

void C$_Prompt(void)
{
    #ifndef NO_PROMPT
    write(STDOUT_FILENO, C$_PROMPT_TEXT, C$_PROMPT_SIZE);
    #endif
}

ssize_t C$_Getline(char * buffer, unsigned size, ssize_t offset, enum rflag * flag)
{
    ssize_t input = read(STDIN_FILENO, buffer + offset, size);
  
  //printf("%u\n", buffer[input + offset - 1]);
    if (buffer[input + offset - 1] != '\n')
       {
	buffer[input + offset] = '\n';
	input += 1;
//	printf("CTRL-D PRESSED\n");
	*flag = WAIT;
    }
    else
    {
	buffer[input + offset] = '\0';
//	printf("ENTER PRESSED\n");
	*flag = DONE;
    }

    return input + offset;
}

void C$_Putline(int fildes, const char line[])
{
    int i;
    const char * pc = line;

    for (i=0; *pc != '\0'; pc++, i++)
	;
    
    write(fildes, line, i);
    write(fildes, NEW_LINE, 1);
}

int C$_Parse(const char input[], char ** arglist, unsigned max)
{
    /* go through and put space-seperated into different new array, return num words */

    
    int n = 0;

    int starti, i, span;
    starti = 0;
    i = 0;
    span = 0;

    while (input[i] != '\0')
    {
	// skip over spaces and newlines
    	for (; input[i] == ' ' || input[i] == '\n'; i++)
	    ;
	// find the start and end index of the next word
	for(starti = i; input[i] != ' ' && input[i] != '\0' && input[i] != '\n'; i++)
	    ;

	// if it is larger than 0, copy the string into the arg list       	
	if ((span = i - starti) > 0)
	{
	    arglist[n] = (char *) malloc(sizeof(char) * (span + 1));
	    memcpy(arglist[n], input + starti, span + 1);
	    arglist[n][span]='\0';
	    n++;
	}
    }    
    return n;
}

void C$_Clrbuffs(unsigned length, char ** arglist, char ** eargv)
{// wipe the input buffers and stop memory leaks

    unsigned i;
    for (i = 0; i < length; i++)
    {
	free(arglist[i]);
	eargv[i] = 0;
	arglist[i] = 0;
    }
}

/* builtin functions */
int C$_Chdir(const char* dirname){

    if(chdir(dirname) == -1){
    	perror("CD Ca$h Error");
    }
    return chdir(dirname);
}

int C$_Link(const char* input, const char* lnk)
{
	if(link(input, lnk) == -1)
	{
	    perror("ca$h: ERROR link");
	}
	return link(input, lnk);
}
	    
int C$_Remove(const char* input)
{
	if (remove(input) == -1)
	{
		perror("ca$h ERROR remove");
	}
	return remove(input);
}
