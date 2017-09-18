#ifndef CASH_H
#define CASH_H

#include <unistd.h>

#define C$_BUFFER_SIZE 1024
#define C$_PROMPT_SIZE 6
#define C$_MAX_ARGS 32

void C$_Prompt(void);
void C$_LS(const char dname[]);
ssize_t C$_Getline(char *, unsigned);
void C$_Putline(int, const char[]);
int C$_Parse(const char[], char **, unsigned);
int C$_Chdir(const char*);

#endif
