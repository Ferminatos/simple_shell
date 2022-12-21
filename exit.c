#include "shell.h"

static int EXIT_CODE;
static int no_init_exit_code = 1;

/**
 * handle_exit - Checks if the user entered the exit command
 * @buff: User's input
 * @cmds_list: Array of parsed commands
 * @commands: User's input parsed as array of commands
 *
 * Return: 0 if the commad is NOT exit, -1 if the exit status was Illegal
*/

int handle_exit(char *buff, char **cmds_list, char **commands)
{
	int status;

	/* Command is NOT exit */
	if (commands[0] == NULL || _strcmp(commands[0], "exit") != 0)
		return (0);

	/* Command is exit */
	if (commands[1] == NULL)
	{
		write_history();
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		if (*process_exit_code() == 127)
			exit(2);
		exit(0);
	}

	status = get_exit_status(commands[1]);
	/* Command is exit status */
	if (status >= 0)
	{
		write_history();
		free_allocs(buff, cmds_list, commands, F_BUFF | F_CMDS);
		exit(status);
	}

	/* the exit status passed was illegal */
	print_builtin_error("exit: Illegal number: ", commands[1]);
	return (-1);
}

/**
 * get_exit_status - Calculates the exit status as a number
 * @buff: User's input
 *
 * Return: Exist status as number, -1 on error
*/
int get_exit_status(char *buff)
{
	int i;
	int status = 0;

	for (i = 0; buff[i] != '\0'; i++)
	{
		if (buff[i] == '\n')
			return (status);

		if (buff[i] < '0' || buff[i] > '9')
			return (-1);

		status *= 10;
		status += buff[i] - '0';
	}

	return (status);
}

/**
 * process_exit_code - Returns the address at which EXIT_CODE is stored
 * Return: Address of EXIT_CODE var
 */

int *process_exit_code()
{
	if (no_init_exit_code)
	{
		EXIT_CODE = 0;
		no_init_exit_code = 0;
	}

	return (&EXIT_CODE);
}

/**
 * set_process_exit_code - Sets the value for EXIT_CODE var
 * @code: Number representing exit code
 */

void set_process_exit_code(int code)
{
	EXIT_CODE = code;
}
