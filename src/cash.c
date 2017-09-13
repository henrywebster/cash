#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "cash.h"

const char * C$_PROMPT_TEXT = "ca$h> ";
const char * NEW_LINE = "\n";

void C$_Prompt(void)
{
    write(STDOUT_FILENO, C$_PROMPT_TEXT, C$_PROMPT_SIZE);
}

void C$_LS(const char dname[])
{
    
    DIR * d = opendir(dname);
    struct dirent * direntry;
    while ((direntry = readdir(d)) != 0)
    {
	C$_Putline(STDOUT_FILENO, direntry->d_name);
    }
    closedir(d);
}

ssize_t C$_Getline(char * buffer, unsigned size)
{
    read(STDIN_FILENO, buffer, size);
}

void C$_Putline(int fildes, const char line[])
{
    int c, i;
    const char * pc = line;

    for (; *pc != '\0'; pc++, i++)
	;
    
    write(fildes, line, i);
    write(fildes, NEW_LINE, 1);
}

int C$_Parse(const char input[], char ** arglist, unsigned max)
{
    /* go through and put space-seperated into different new array */
    // add const to arglist?
    
    int c, i, n;

    int starti = 0;

    for (c = input[i], n = 0; input[i] != '\0'; i++)
    {
	if (c == ' ')
	{
	    int span = i - starti;
	    arglist[n] = (char *) malloc(sizeof(char) * span + 1);
	    memcpy(arglist[n], input + i, span);
	    C$_Putline(STDOUT_FILENO, arglist[n]);
	    arglist[n++][span + 1] = '\n';
	}
    }
}
    
	    
    
