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

void C$_LS(const char dname[])
{

    printf("DNAME: %s\n", dname);
    if (!dname){
    	dname = ".";
    }
    DIR * d;
    if ((d = opendir(dname)) == 0)
    {
	perror("ERROR in LS");
    }
    else
    {
    struct dirent * direntry;
    while ((direntry = readdir(d)) != 0)
    {
	C$_Putline(STDOUT_FILENO, direntry->d_name);

    }
    closedir(d);
    }
}

ssize_t C$_Getline(char * buffer, unsigned size)
{
    ssize_t input = read(STDIN_FILENO, buffer, size);
    buffer[input] = '\0';
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

int C$_Parse(const char input[], char ** arglist, unsigned max)
{
    /* go through and put space-seperated into different new array, return num words */

    
    int n = 0;

    int starti = 0;
    int i = 0;
    int span;

    while (input[i] != '\0')
    {
	// skip over spaces and newlines
    	for (; input[i] == ' ' || input[i] == '\n'; i++)
	    ;
	// find the start and end index of the next word
	for(starti = i; input[i] != ' ' && input[i] != '\0' && input[i] != '\n'; i++)
	    ;

	// if it is larger than 0, copy the string into the arg list
	
	
	if ((span = i-starti) > 0)
	{
	    arglist[n] = (char*) malloc(sizeof(char)*(span+1));
	    memcpy(arglist[n], input+starti, span+1);
	    arglist[n][span]='\0';
	    //printf("[%d]%d: %s\n", n, span, arglist[n]);
	    n++;
	}
    }    
    return n;
}

void C$_ClearArgs(char ** arglist, unsigned length)
{
    unsigned i;
    for (i = 0; i < length; i++)
    {
	free(arglist[i]);
	arglist[i] = 0;
    }
}


int C$_Chdir(const char* dirname){


    if(chdir(dirname) == -1){
    	perror("CD Ca$h Error");
    }
    return chdir(dirname);
}

int C$_LN(const char* input, const char* lnk){
	if(link(input, lnk) == -1){
    	perror("LN Ca$h Error");
    }
	return link(input, lnk);
}
	    
int C$_RM(const char* input){
	if(remove(input)==-1){
		perror("RM Ca$h Error");
	}
	return remove(input);
}
