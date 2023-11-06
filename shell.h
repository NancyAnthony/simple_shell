#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @number the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int number;
	char *string;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int his_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* handle_shell_loop.c */
int hsh(info_t *, char **);
int check_builtin(info_t *);
void check_cmd(info_t *);
void fork_cmd(info_t *);

/* handle_parser.c */
int check_is_cmd(info_t *, char *);
char *duplicate_char(char *, int, int);
char *check_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errs.c */
void _epts(char *);
int eputschar(char);
int _pfd(char b, int fde);
int _psfd(char *_str, int fde);

/* handle_string.c */
int string_len(char *);
int string_cmp(char *, char *);
char *check_start(const char *, const char *);
char *string_cat(char *, char *);

/* handle_string1.c */
char *string_copy(char *, char *);
char *string_dupp(const char *);
void get_puts(char *);
int _echar(char);

/* exit.c */
char *_strcp(char *, char *, int);
char *str_cat(char *, char *, int);
char *st_ch(char *, char);

/* handle_token.c */
char **splwrd(char *, char *);
char **splwrd2(char *, char);

/* handle_reallocate_mem.c */
char *memory_set(char *, char, unsigned int);
void str_free(char **);
void *_reallocate_mem(void *, unsigned int, unsigned int);

/* handle_memory.c */
int be_free(void **);

/* handles_atoi.c */
int check_interactive(info_t *);
int check_delimeter(char, char *);
int check_isalpha(int);
int handle_atoi(char *);

/* err_1.c */
int cv_str(char *);
void prt_err(info_t *, char *);
int print_de(int, int);
char *convert_no(long int, int, int);
void rm_comments(char *);

/* builtin0.c */
int my_exits(info_t *);
int _cd(info_t *);
int _myhelper(info_t *);

/* builtin1.c */
int handle_myhistory(info_t *);
int _myalias(info_t *);

/*get_line.c */
ssize_t _getinput(info_t *);
int get_line(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t chain_buff(info_t *, char **, size_t *);

/* get_information.c */
void cleared_inf(info_t *);
void set_infor(info_t *, char **);
void free_infor(info_t *, int);

/* get_environ.c */
char *get_environ(info_t *, const char *);
int my_environ(info_t *);
int myset_environ(info_t *);
int my_unset_environ(info_t *);
int pop_environ_list(info_t *);

/* get_envy.c */
char **get_envy(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* handle_history.c */
char *get_history(info_t *myinfo);
int wrt_historyfile(info_t *myinfo);
int handle_readhistory(info_t *myinfo);
int handle_history_list(info_t *myinfo, char *buffer, int ln_count);
int renum_history(info_t *myinfo);

/* handle_lists.c */
list_t *handle_node(list_t **, const char *, int);
list_t *handle_node_end(list_t **, const char *, int);
size_t print_string(const list_t *);
int handle_delete_node_index(list_t **, unsigned int);
void _freelist(list_t **);

/* handle_lists1.c */
size_t handle_list_len(const list_t *);
char **handle_list_to_str(list_t *);
size_t handle_prnt_list(const list_t *);
list_t *node_start_with_prefix(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* handle_vars.c */
int check_ischain(info_t *, char *, size_t *);
void handles_chain(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_vars(info_t *);
int rep_str(char **, char *);

#endif
