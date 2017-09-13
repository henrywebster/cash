#include "cash.h"

int main(int argv, char * argc[])
{
    char buffer[C$_BUFFER_SIZE];
    ssize_t size = 1;

    while (size > 0)
    {
	C$_Prompt();
	size = C$_Getline(buffer, C$_BUFFER_SIZE);
    }

    return 0;
}
