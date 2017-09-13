#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

#define BUFFER_SIZE 256
#define PROMPT_SIZE 6

const char * PROMPT_TEXT = "ca$h> ";

void C$_Prompt(void);
void C$_LS(void);
ssize_t C$_Getline(char *, unsigned);
int C$_Parse(const char[]);

int main(int argc, char * argv[])
{

    char buffer[BUFFER_SIZE];
    ssize_t size = 1;
    
    while (size > 0)
    {

	C$_Prompt();
	size = C$_Getline(buffer, BUFFER_SIZE);

    }
//	size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
//	write(STDOUT_FILENO, buffer, size);


    C$_LS();

	



    return 0;
}

void C$_Prompt(void)
{
    write(STDOUT_FILENO, PROMPT_TEXT, PROMPT_SIZE);
}

void C$_LS(void)
{
    DIR * d = opendir(".");
    struct dirent * direntry;
    while ((direntry = readdir(d)) != 0)
    {
	printf("%s\n", direntry->d_name);
    }
}

ssize_t C$_Getline(char * buffer, unsigned size)
{
    return read(STDIN_FILENO, buffer, size);
}
