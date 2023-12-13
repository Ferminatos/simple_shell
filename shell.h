#ifndef __SHELL_H
#define __SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

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

size_t print_list(const list_t *h);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);

char *get_first_av(void);
char *_getenv(char *name);

int execute_commands(char *buff, char **cmds_list, char *cmd,
			int read, char *first_av);

void __attribute__((constructor)) build_dynamic_environ(void);
void __attribute__((destructor)) free_dynamic_environ(void);

void env(void);
int _setenv(char *name, char *value);
int _unsetenv(char *name);

list_t **get_last_cmd_addrss();

int validate_env_name(char *name);
int is_valid_env_var_name(char *name);
int get_env_index(char *name);

char *_strtok(char *str, char *delimiter);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);

int handle_PATH(char **commands);
char **parse_user_input(char *str_input, char *delimiter);
int count_args(char *str_input, char *delimiter);

void *allocate_memory(unsigned int bytes);
char *duplicate_string(char *str);
void free_dbl_ptr(char **dbl_ptr);
void free_allocs(char *buff, char **cmds_list, char **commands, int flags);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int handle_builtins(char **commands);

int handle_enter(char **commands);

int handle_exit(char *buff, char **cmds_list, char **commands);
int get_exit_status(char *buff);
int *process_exit_code();
void set_process_exit_code(int code);

void dispatch_error(char *msg);
void print_builtin_error(char *msg, char *arg);

int _strlen(const char *s);
char *_strdup(const char *s1);
char *_strchr(const char *s, int c);
char *_strcat(char *s1, const char *s2);
char *_strncat(char *s1, const char *s2, size_t n);
char *num_to_str(int num);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(const char *s1, const char *s2);
int _puts(char *str);
#endif
