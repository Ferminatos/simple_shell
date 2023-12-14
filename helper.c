#include "shell.h"

static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

/**
 * write_history - Writes the history to a file in home dir
*/
void write_history(void)
{
	list_t *curr;
	int fd;
	char *home;

	home = _getenv("HOME");
	if (home == NULL)
		home = "/";

	if (chdir(home) == -1)
		return;

	fd = open(".simple_shell_history", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return;

	for (curr = *get_history_addrss(); curr != NULL; curr = curr->next)
	{
		write(fd, curr->str, curr->len);
		write(fd, "\n", 1);
	}

	close(fd);
}

/**
 * get_history_addrss - Return the address oof history head
 *
 * Return: Address of history head
*/

list_t **get_history_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&history_head);
}

/**
 * get_last_cmd_addrss - Return the address oof history head
 *
 * Return: Address of last entered command
*/
list_t **get_last_cmd_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&last_cmd);
}

/**
 * _history - Prints the all the commands entered by the user
 *
 * Return: 1 on success
*/
int _history(void)
{
	list_t *curr;
	char *str_num;
	int i, len;
	int count = *get_history_lines_count() % 4096;

	for (curr = *get_history_addrss(); curr != NULL; curr = curr->next)
	{
		str_num = num_to_str(count++);
		len = _puts(str_num);
		for (i = len; i < 7; i++)
			_puts(" ");
		_puts(curr->str);
		_puts("\n");
		free(str_num);
	}

	return (1);
}

/**
 * handle_history - Adds a command to the history
 * @buff: User's input
*/
void handle_history(char *buff)
{
	if (last_cmd == NULL || buff[0] != ' ' || _strcmp(last_cmd->str, buff) != 0)
		last_cmd = add_node_end(get_history_addrss(), buff);
}

