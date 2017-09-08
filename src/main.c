#include <stdio.h>

#define BUFFER_SIZE 256

int getinput(char[]);

int main(int argc, char * argv[])
{

    int i = 1;
    char buffer[BUFFER_SIZE];
    char * garbage;

    while (i > 0)
    {
	/* the prompt */
	printf("ca$h> ");

	/* read input */
	i = getinput(buffer);
    }
    
    return 0;
}

int getinput(char s[])
{
    int i, c;

    for (i = 0; (c = getchar()) != EOF; i++)
    {
	if ('\n' == c)
	   break;
	s[i] = c;
    }
    s[i] = '\0';
    return i;
}
