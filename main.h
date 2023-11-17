#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_histoy"
#define HIST_MAX	4096

extern char **environ;

/** 
 * struct liststr - node struct
 * strstr - singly linked list
 * @num: number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
  * struct passvar - struct containing common variables
  * @arg: argument
  * @argv: argument vector
  * @path: path varable
  * @argc: argument count
  * @ln_count: line count
  * @num_error: error number
  * @ln_count_flag: store linecount flag
  * @file_name: file name
  * @env: environment list
  * @history: history list
  * @alias: alias list
  * @environ: enviroment variable
  * @envi_change: enviroment changed to
  * @status: return status of child
  * @cmd_buff: command bufffer
  * @cmd_buff_type: command bufffer type
  * @readfile: readfile status
  * @histcount: history count
  */
typedef struct passvar
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int ln_count;
	int num_error;
	int ln_count_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envi_change;
	int status;
	char **cmd_buff;
	int cmd_buff_type;
	int readfile;
	int histcount;
} vars_t;

#define VAR_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
  * struct builtin - contain builtin variables and related function
  *@type: n cnd flag
  *@func: the func
 */
typedef struct builtin
{
	char *type;
	int (*func)(vars_t *);
} builtin_table;
	

/* prototypes */
int shell_loop(vars_t *, char **);
int find_builtin(vars_t *);
void find_cmd(vars_t *);
void fork_cmd(vars_t *);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_strtok(char *, char *);
char **_strtok2(char *, char);
int is_command(vars_t *, char *);
char *dup_char(char *, int, int);
char *_fpath(vars_t *, char *, char *);
int loopshell_loop(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
char *_memo_set(char *, char, unsigned int);
void __sfree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int _pfree(void **);
int is_interactive(vars_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _err_atoi(char *);
void _perror(vars_t *, char *);
int _print_dec(int, int);
char *_itoa(long int, int, int);
void rm_comments(char *);
int _shellexit(vars_t *);
int _change_dir(vars_t *);
int _help(vars_t *);
char *find_history(vars_t *var);
int w_history(vars_t *var);
int r_history(vars_t *var);
int build_history(vars_t *var, char *buff, int linecount);
int renum_history(vars_t *var);
list_t *add_nodeint(list_t **, const char *, int);
list_t *add_nodeintint_end(list_t **, const char *, int);
size_t print_list_s(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain_delim(vars_t *, char *, size_t *);
void check_chain(vars_t *, char *, size_t *, size_t, size_t);
int replace_alias(vars_t *);
int replace_vars(vars_t *);
int replace_string(char **, char *);
int _history(vars_t *);
int _alias(vars_t *);
ssize_t get_input(vars_t *);
int _getline(vars_t *, char **, size_t *);
void _signhandler(int);
void clear_var(vars_t *);
void set_var(vars_t *, char **);
void free_var(vars_t *, int);
char *_get_environ(vars_t *, const char *);
int _environ(vars_t *);
int _set_environ(vars_t *);
int _unset_environ(vars_t *);
int pop_environ_list(vars_t *);
char **get_environ(vars_t *);
int _unsetenviron(vars_t *, char *);
int _setenviron(vars_t *, char *, char *);

#endif
