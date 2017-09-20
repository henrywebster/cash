#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

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
  
    if (input && buffer[input + offset - 1] != '\n')
    { // [Extra credit] CTRL-D pressed with previous input (input read != 0)
	buffer[input + offset] = '\n';
	input += 1;
	C$_Putline(STDOUT_FILENO, "");
	*flag = WAIT;
    }
    else
    { // [Extra credit] ENTER or CTRL-D with no previous input pressed
	buffer[input + offset] = '\0';
	*flag = DONE;
    }

    return input;
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

int C$_Parse(const char input[], char ** arglist, unsigned max, char ** infile, char ** outfile, enum rmode * mode)
{
    /* go through and put space-seperated into different new array, return num words */
    int n = 0;

    int starti, endi, i, span;
    starti = 0;
    endi = 0;
    i = 0;
    span = 0;

    int inflag = 0;
    int outflag = 0;

    while (input[i] != '\0')
    {
	// skip over spaces and newlines
    	for (; input[i] == ' ' || input[i] == '\n' || input[i] == '\t'; i++)
	    ;
	// find the start and end index of the next word
	for(starti = i; input[i] != '<' && input[i] != '>' && input[i] != ' ' && input[i] != '\0' && input[i] != '\n' && input[i] != '\t'; i++, endi = i)
	    ;


	// if it is larger than 0, copy the string into the arg list       	
	if ((span = endi - starti) > 0)
	{
	if (inflag == 1)
	{
	    free(*infile);
	    *infile = (char *) malloc(sizeof(char) * (span + 1));
	    memcpy(*infile, input + starti, span + 1);
	    *(*infile + span) = '\0';
	    inflag = -1;
	}
	else if (outflag == 1)
	{
	    free(*outfile);
	    *outfile = (char *) malloc(sizeof(char) * (span + 1));
	    memcpy(*outfile, input + starti, span + 1);
	    *(*outfile + span) = '\0';
	    outflag = -1;
	}
	else
	{
	    arglist[n] = (char *) malloc(sizeof(char) * (span + 1));
	    memcpy(arglist[n], input + starti, span + 1);
	    arglist[n][span]='\0';
	    n++;
	}
	}

	if (input[i] == '<')
	{
	    endi = i;
	    i++;
	    inflag = 1;
	}
	if (input[i] == '>')
	{
	    endi = i;
	    i++;
	    if (input[i] == '>')
	    {	
		i++;
		*mode = APPEND;
	    }
	    else
		*mode = QUASH;
	    
	    outflag = 1;
	}
    }    
    
    return n;
}

int C$_Redirect(const char const * infile, const char const * outfile, const enum rmode mode)
{
    printf("my input: %s\n", infile);
    int fi, flags;

    flags = O_CREAT | O_WRONLY;
    
    if (infile)
    {
	close(STDIN_FILENO);
	if ((fi = open(infile, O_RDONLY) == -1))
	{
	    perror("ca$h ERROR: Cannot redirect input");
	    return -1;
	}
    }
    if (outfile)
    {
	close(STDOUT_FILENO);
	if (mode == APPEND)
	    flags |= O_APPEND;
	else
	    flags |= O_TRUNC;
	if ((fi = open(outfile, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1))
	{
	    perror("ca$h ERROR: Cannot redirect output");
	    return -1;
	}
    }
    return 0;
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
int C$_Chdir(const char* dirname)
{
    int val = chdir(dirname);
    if(val == -1){
    	perror("ca$h: ERROR chdir");
    }
    return val;
}

int C$_Link(const char* input, const char* lnk)
{
    int val = link(input, lnk);
    if(val == -1)
    {
	perror("ca$h: ERROR link");
    }
    return val;
}
	    
int C$_Remove(const char* input)
{
    int val = remove(input);
    if (val == -1)
    {
	perror("ca$h ERROR remove");
    }
    return val;
}
