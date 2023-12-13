#include "shell.h"

/**
 * dispatch_error - Dispatches an error
 * @msg: Message to print as error
*/

void dispatch_error(char *msg)
{
	perror(msg);
	exit(errno);
}

/**
 * print_builtin_error - Prints error for buitin function
 * @msg: Error message
 * @arg: Argument
*/
void print_builtin_error(char *msg, char *arg)
{
	int len = _strlen(msg);
	char *first_av = get_first_av();

	write(STDERR_FILENO, first_av, _strlen(first_av));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, msg, len);
	write(STDERR_FILENO, arg, _strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	set_process_exit_code(2);
}
