#if !defined(HEADER_H)
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //_getcwd()
#include <direct.h> //_chdir() 

#define MINISHELL_PATH_MAX MAX_PATH

// Command table 
typedef char *(*command_fn)(char *buf, size_t bufsize);
typedef struct {
    const char *name;
    command_fn fn;
    const char *desc;
} command_t;

//redifining bcs .h files contain commands with same name fuck!!!!!!!!!!!
#define rename rename_impl
#define open   open_impl
#define rmdir  rmdir_impl
#define write  write_impl
// --- command function prototypes ---
char *whereami(char *buf, size_t bufsize);
char *whoami(char *buf, size_t bufsize);
char *echo(char *buf, size_t bufsize);
char *help(char *buf, size_t bufsize);
char *help_error(char *buf, size_t bufsize);
char *cd(char *buf, size_t bufsize);
char *list(char *buf, size_t bufsize);
char *ls(char *buf, size_t bufsize);
char *create(char *buf, size_t bufsize);
char *crt(char *buf, size_t bufsize);
char *rename(char *buf, size_t bufsize);   //rename_impl
char *rnm(char *buf, size_t bufsize);
char *del(char *buf, size_t bufsize);
char *rem(char *buf, size_t bufsize);
char *deletedirective(char *buf, size_t bufsize);
char *deldir(char *buf, size_t bufsize);
char *rmdir(char *buf, size_t bufsize);
char *move(char *buf, size_t bufsize);
char *mv(char *buf, size_t bufsize);
char *open(char *buf, size_t bufsize);     //open_impl
char *op(char *buf, size_t bufsize);
char *open2(char *buf, size_t bufsize);
char *op2(char *buf, size_t bufsize);
char *delete(char *buf, size_t bufsize);
char *write(char *buf, size_t bufsize);   // write_impl

#endif // HEADER_H
