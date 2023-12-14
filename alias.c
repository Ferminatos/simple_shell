#include "shell.h"

static int not_init_alias_head = 1;
static list_t *alias_head;

/**
 * get_alias_head - Returns alias_head pointer
 *
 * Return: Pointer to alias head var
*/

list_t **get_alias_head()
{
	if (not_init_alias_head == 1)
	{
		alias_head = NULL;
		not_init_alias_head = 0;
	}
	return (&alias_head);
}

/**
 * is_set_alias - Checks if the alias input is meant to set an alias
 * @alias_pair: String as alias arg input
 *
 * Return: 1 for true, 0 otherwise
*/
int is_set_alias(char *alias_pair)
{
	int i;

	for (i = 1; alias_pair[i] != '\0'; i++)
		if (alias_pair[i] == '=')
			return (1);

	return (0);
}

/**
 * set_alias - adds aliases
 * @alias_pair: String in the form name=value
*/
void set_alias(char *alias_pair)
{
	char tmp_buff[250];
	int first_eq, last_eq;
	list_t *curr;
	list_t **alias_addrs = get_alias_head();

	for (first_eq = 1; alias_pair[first_eq] != '\0'; first_eq++)
		if (alias_pair[first_eq] == '=')
			break;

	strncpy(tmp_buff, alias_pair, first_eq);
	tmp_buff[first_eq] = '\0';
	_strcat(tmp_buff, "='");

	for (last_eq = first_eq; alias_pair[last_eq] != '\0'; last_eq++)
		if (alias_pair[last_eq] != '=')
			break;

	_strcat(tmp_buff, &alias_pair[last_eq]);
	_strcat(tmp_buff, "'");

	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		if (_strncmp(curr->str, alias_pair, first_eq) == 0 &&
				(curr->str)[first_eq] == '=')
		{
			free(curr->str);
			curr->str = _strdup(tmp_buff);
			return;
		}

	add_node_end(alias_addrs, tmp_buff);
}

/**
 * handle_alias_args - Evaluates alias input command and decides what to do
 * @commands: Arrays of commands
 * @out_addrs: Pointer to out's head node
 *
 * Return: -1 if error happens, 0 otherwise
*/
int handle_alias_args(char **commands, list_t **out_addrs)
{
	int i, len, was_alias;
	int status = 0;
	list_t *curr;
	list_t **alias_addrs = get_alias_head();

	set_process_exit_code(0);
	for (i = 1; commands[i] != NULL; i++)
	{
		was_alias = 0;
		len = _strlen(commands[i]);

		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			if (_strncmp(curr->str, commands[i], len) == 0 && (curr->str)[len] == '=')
			{
				was_alias = 1;
				add_node_end(out_addrs, curr->str);
				break;
			}
		}
		if (was_alias)
			continue;

		if (is_set_alias(commands[i]))
			set_alias(commands[i]);
		else
		{
			status = -1;
			set_process_exit_code(1);
			_puts("alias: ");
			_puts(commands[i]);
			_puts(" not found\n");
		}
	}

	return (status);
}

/**
 * handle_aliases - Handle alias
 * @commands: Arrays of commands
*/
void handle_aliases(char **commands)
{
	list_t *curr;
	list_t **alias_addrs = get_alias_head();
	int cmd_len = _strlen(commands[0]);
	char *str;
	char tmp_buff[250];
	int i, alias_len = 0;

	if (commands[0] == NULL)
		return;

	for (i = 0; i < 250; i++)
		tmp_buff[i] = '\0';

	for (curr = *alias_addrs; curr != NULL; curr = curr->next)
	{
		str = curr->str;
		if (_strncmp(commands[0], str, cmd_len) == 0 && str[cmd_len] == '=')
		{
			alias_len = _strlen(&str[cmd_len + 2]);
			strncpy(tmp_buff, &str[cmd_len + 2], alias_len - 1);
			tmp_buff[alias_len] = '\0';
			free(commands[0]);
			commands[0] = duplicate_string(tmp_buff);
			break;
		}
	}
}

