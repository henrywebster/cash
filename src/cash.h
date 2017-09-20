#ifndef CASH_H
#define CASH_H

#include <unistd.h>

#define C$_BUFFER_SIZE 1024
#define C$_PROMPT_SIZE 6
#define C$_MAX_ARGS 32

enum rflag {DONE, WAIT};
enum rmode {QUASH, APPEND};

void C$_Prompt(void);
ssize_t C$_Getline(char *, unsigned, ssize_t, enum rflag *);
void C$_Putline(int, const char[]);
int C$_Parse(const char[], char **, unsigned, char **, char **, enum rmode *);
int C$_Redirect(const char const *, const char const *, const enum rmode);
void C$_Clrbuffs(unsigned, char **, char **);
int C$_Chdir(const char*);
int C$_Link(const char*, const char*);
int C$_Remove(const char*);


#endif
