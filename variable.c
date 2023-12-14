#include "shell.h"

/**
 * handle_var_replacement - Handles variables replacement
 * @commands: Array of commands
*/

void handle_var_replacement(char **commands)
{
	int i;
	char *env_val;

	if (commands[0] == NULL)
		return;

	for (i = 1; commands[i] != NULL; i++)
	{
		if (commands[i][0] != '$')
			continue;

		if (_strcmp(&commands[i][1], "?") == 0)
		{
			free(commands[i]);
			commands[i] = num_to_str(*process_exit_code());
			return;
		}

		if (_strcmp(&commands[i][1], "$") == 0)
		{
			free(commands[i]);
			commands[i] = num_to_str(getpid());
			return;
		}

		env_val = _getenv(&commands[i][1]);
		if (env_val != NULL)
		{
			free(commands[i]);
			commands[i] = duplicate_string(env_val);
		}
	}
}
