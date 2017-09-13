#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 256
#define PROMPT_SIZE 6

#define MAX_INPUT_ARGS 32

const char * PROMPT_TEXT = "ca$h> ";
const char * NEW_LINE = "\n";

void C$_Prompt(void);
void C$_LS(const char dname[]);
ssize_t C$_Getline(char *, unsigned);
void C$_Putline(int, const char []);
int C$_Parse(const char [], char **, unsigned);

int main(int argc, char * argv[])
{

    char buffer[BUFFER_SIZE];
    char * argbuffer[MAX_INPUT_ARGS];
    ssize_t size = 1;
    
    while (size > 0)
    {

	C$_Prompt();
	size = C$_Getline(buffer, BUFFER_SIZE);
	C$_Parse(buffer, argbuffer, MAX_INPUT_ARGS);
	/*
	if (strncmp(buffer, "ls", size - 1) == 0)
	{
	    C$_LS();
	}
	*/

    }

    return 0;
}

void C$_Prompt(void)
{
    write(STDOUT_FILENO, PROMPT_TEXT, PROMPT_SIZE);
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
    return read(STDIN_FILENO, buffer, size);
}

void C$_Putline(int fildes, const char line[])
{
    int c, i;

    for (c = line[i]; line[i] != '\0'; i++)
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
    
	    
    
