#include "shell.h"

/**
 * parse_user_input - Builds an array of strings as arguments
 * @str_input: Command input given by the user
 * @delimiter: String of chars indicating the delimiters
 *
 * Return: Array of strings
*/

char **parse_user_input(char *str_input, char *delimiter)
{
	int i, args_count = 0;
	char **args;
	char *token, *tkn_ptr;
	char *str_copy;

	if (str_input == NULL)
		dispatch_error("Error while parsing the command\n");

	args_count = count_args(str_input, delimiter);
	args = allocate_memory(sizeof(char *) * (args_count + 1));
	str_copy = duplicate_string(str_input);
	tkn_ptr = str_copy;

	for (i = 0; i < args_count; i++)
	{
		token = _strtok(tkn_ptr, delimiter);
		if (token == NULL)
			break;
		tkn_ptr = NULL;
		args[i] = duplicate_string(token);
	}
	args[i] = NULL;
	free(str_copy);

	return (args);
}

/**
 * count_args - Counts the number of arguments in a command string
 * @str_input: Command
 * @delimiter: Delimiter to separate the args
 *
 * Return: Number of arguments present in str_input
*/
int count_args(char *str_input, char *delimiter)
{
	char *tkn, *tkn_ptr;
	int count = 0;
	char *str_copy = duplicate_string(str_input);

	tkn_ptr = str_copy;
	while ((tkn = _strtok(tkn_ptr, delimiter)) != NULL)
	{
		count++;
		tkn_ptr = NULL;
	}

	free(str_copy);

	return (count);
}

/**
 * handle_PATH - Checks if the command to execute could be found in PATH's dirs
 * @commands: Array of strings containing the command and args
 * Return: flag 0 if success; -1 if  error
*/
int handle_PATH(char **commands)
{
	char *path_dirs;
	int flag = 127;

	if (
		commands == NULL || commands[0] == NULL ||
		commands[0][0] == '\0' || commands[0][0] == '/'
	)
		return (127);

	if (access(commands[0], F_OK) == 0)
		return (0);

	path_dirs = _getenv("PATH");
	if (path_dirs == NULL)
		return (127);

	return (flag);
}
