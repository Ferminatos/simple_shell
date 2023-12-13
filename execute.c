#include "shell.h"

void handle_cmd_not_found(char *buff, char **cmds_list, char **commands,
	char *first_av);
/**
 * handle_enter - Check if no command was entered
 * @commands: String of commnands
 * Return: 1 if no command was entered, 0 otherwise
 */

int handle_enter(char **commands)
{
	if (commands[0] == NULL || _strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}

/**
 * execute_commands - Fork and create commands, child process and executed
 * @buff: The first buffer function reads
 * @cmds_list: List of commands
 * @cmd: A single command
 * @read: return of read
 * @first_av: The first element of the argument array
 * Return: 0 on success
 */

int execute_commands(char *buff, char **cmds_list,
	char *cmd, int __attribute__((unused))read, char *first_av)
{
	char **commands;
	int child_pid, _err = 0, flag = 0, *status = process_exit_code();

	commands = parse_user_input(cmd, " ");

	if (handle_exit(buff, cmds_list, commands) == -1 ||
			handle_enter(commands) == 1	||
			handle_builtins(commands) == 1)
	{
		free_dbl_ptr(commands);
		return (-1);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		dispatch_error(first_av);
	}

	else if (child_pid == 0)
	{
		_err = handle_PATH(commands);
		execve(commands[0], commands, __environ);
		if (_err != 0)
			handle_cmd_not_found(buff, cmds_list, commands, first_av);
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
		dispatch_error(first_av);
	}
	wait(status);
	*status = WEXITSTATUS(*status);
	if (*status == 2)
		set_process_exit_code(127);
	free_dbl_ptr(commands);

	return (flag);
}

/**
 * handle_cmd_not_found - Print a message to stderr
 * @buff: User's input
 * @cmds_list: Array of commands
 * @commands: Array of strings
 * @first_av: First argument passed to the executable
 */

void handle_cmd_not_found(char *buff, char **cmds_list, char **commands,
	char *first_av)
{
	set_process_exit_code(127);
	write(2, first_av, _strlen(first_av));
	write(2, ": 1: ", 5);
	write(2, commands[0], _strlen(commands[0]));
	write(2, ": not found\n", 12);
	free_allocs(buff, cmds_list, commands, F_BUFF | F_CMD_L | F_CMDS);
	exit(127);
}
