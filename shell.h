#ifndef SHELL_H_
#define SHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
/* open */
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/* FLAGS */
#define F_BUFF 1
#define F_CMD_L 2
#define F_CMDS 4

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

/*linked lists*/
size_t print_list(const list_t *h);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);

char *get_first_av(void);

int execute_commands(char *buff, char **cmds_list, char *cmd,int read, char *first_av);

/* Special functions */
void __attribute__((constructor)) build_dynamic_environ(void);
void __attribute__((destructor)) free_dynamic_environ(void);

char *_getenv(char *name);

int *process_exit_code();
void set_process_exit_code(int code);

/* builtins */
void env(void);
int _setenv(char *name, char *value);
int _unsetenv(char *name);
int _help(char **commands);

/* builtins utils */
int validate_env_name(char *name);
int is_valid_env_var_name(char *name);
int get_env_index(char *name);
/* functions that is part of help */
int read_line(const int fd, char **line);
int f_read_line(char **str, char **line, int fd);

/* own implementations */
char *_strtok(char *str, char *delimiter);
int _getline(char **buffer, size_t *buf_size, FILE *stream);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);

/* Command handlers */
int handle_PATH(char **commands);
char *getpath(char *dir, char *filename);
char **parse_user_input(char *str_input, char *delimiter);
int count_args(char *str_input, char *delimiter);

/* Memory management */
void *allocate_memory(unsigned int bytes);
char *duplicate_string(char *str);
void free_dbl_ptr(char **dbl_ptr);
void free_allocs(char *buff, char **cmds_list, char **commands, int flags);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* handle_builtins */
int handle_builtins(char **commands);

/* handle_enter */
int handle_enter(char **commands);
/* handle comments in input */
char *handle_comment(char *str_input);

/* Exit handlers */
int handle_exit(char *buff, char **cmds_list, char **commands);
int get_exit_status(char *buff);

/* Error handlers */
void dispatch_error(char *msg);
void print_builtin_error(char *msg, char *arg);

/* strings functions */
int _strlen(const char *s);
char *_strdup(const char *s1);
char *_strchr(const char *s, int c);
char *_strcat(char *s1, const char *s2);
char *_strncat(char *s1, const char *s2, size_t n);
char *num_to_str(int num);
int _strncmp(const char *s1, const char *s2, size_t n);
int _puts(char *str);

/* f_strings_creations */
char *f_strjoin(char const *s1, char const *s2);
char *f_strsub(char const *s, unsigned int start, size_t len);
void f_strdel(char **as);
int _strcmp(const char *s1, const char *s2);

#endif
