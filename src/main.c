#include "cash.h"

int main(int argv, char * argc[])
{
    char buffer[C$_BUFFER_SIZE];
    char* argbuffer[64];
    ssize_t size = 1;

    while (size > 0)
    {
	C$_Prompt();
	size = C$_Getline(buffer, C$_BUFFER_SIZE);
	C$_Parse(buffer, argbuffer, size);
    }

    return 0;
}
