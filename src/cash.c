#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


#include "cash.h"

const char * C$_PROMPT_TEXT = "ca$h> ";
const char * NEW_LINE = "\n";

void C$_Prompt(void)
{
    write(STDOUT_FILENO, C$_PROMPT_TEXT, C$_PROMPT_SIZE);
}

void C$_LS(const char dname[])
{
    if (dname ==0){
    	dname = ".";
    }
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
    
    int c;
    int n = 0;

    int starti = 0;
    int i = 0;
    int span;
	//printf("%s \n", input);
    //for (c = input[0], n = 0, i=0; input[i] != '\0'; i++)
    while (input[i] != '\0')
    {
    	for (; input[i] == ' ' || input[i] == '\n'; i++)
    	;
    
	
		for(starti = i; input[i] != ' ' && input[i] != '\0' && input[i] != '\n'; i++)
			;
		if ((span = i-starti) >0){
		arglist[n] = (char*) malloc(sizeof(char)*(span+1));
		memcpy(arglist[n], input+starti, span);
		arglist[n][span+1]='\0';
		//printf("%d:%s \n", n, arglist[n]);
		n++;
		}
		
	    
	    //C$_Putline(STDOUT_FILENO, input);
	}    
    return 0;
}

int C$_Chdir(const char* dirname){

	if(chdir(dirname) == -1){
		if (errno == ENOENT)
		{
			printf("ERROR: does not exist \n", errno);
		}
		if (errno == EACCES){
			printf("ERROR: search permission denied \n", errno);
		}
		if (errno == ELOOP){
			printf("ERROR: too many symbolic links in resolving path \n", errno);
		}
		if (errno == ENAMETOOLONG){
			printf("ERROR: path too long \n", errno);
		}
		if (errno == ENOTDIR){
			printf("ERROR: not a directory \n", errno);	
		}
	}
	return chdir(dirname);



}
	    
    
