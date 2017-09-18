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
    /* go through and put space-seperated into different new array */
    // add const to arglist?
    
    int c, n;

    int starti = 0;
    int i = 0;
    int span;
	printf("%s \n", input);
    //for (c = input[0], n = 0, i=0; input[i] != '\0'; i++)
    while (input[i] != '\0')
    {
    	for (; input[i] == ' '; i++)
    	;
    
	
		for(starti = i; input[i] != ' ' && input[i] != '\0'; i++)
			;
		span = i-starti;
		printf("%d \n", span);

		
	    
	    //C$_Putline(STDOUT_FILENO, input);
	}    
    return 0;
}
    
	    
    
