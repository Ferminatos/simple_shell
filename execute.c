#include "shell.h"

static int EXIT_CODE;

static int no_init_exit_code = 1;

/**
 * process_exit_code - Returns the address at which EXIT_CODE is stored
 *
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

/**
 * build_dynamic_environ - Builds the "env vars" array using dynamic memory
 */

void build_dynamic_environ(void)
{
	int count_envs = 0;
	char **new_environ;

	while (__environ[count_envs] != NULL)
		count_envs++;

	new_environ = allocate_memory(sizeof(char *) * (count_envs + 1));

	for (count_envs = 0;  __environ[count_envs] != NULL; count_envs++)
		new_environ[count_envs] = duplicate_string(__environ[count_envs]);

	/* Last element should be NULL */
	new_environ[count_envs] = NULL;
	/* Asign new memory dynamically allocated */
	__environ = new_environ;
}

/**
 * free_dynamic_environ - Frees the memory allocated to hold "env vars"
 */

void free_dynamic_environ(void)
{
	free_dbl_ptr(__environ);
}


/**
 * handle_enter - Check if no command was entered
 * @commands: String of commnands
 * Return: 1 if no command was entered(just spaces and ENTER), 0 otherwise
 */

int handle_enter(char **commands)
{
	if (commands[0] == NULL || _strcmp(commands[0], "\n") == 0)
		return (1);

	return (0);
}
