#include "shell.h"

/**
 * env - Prints the environment variables to stdout
*/
void env(void)
{
	int i;
	char **env = __environ;

	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	set_process_exit_code(0);
}

/**
 * _setenv - Sets or adds an environment variable
 * @name: Name for the new env variable
 * @value: Value for the new env variable
 *
 * Return: 1 on success, -1 on error
 */
int _setenv(char *name, char *value)
{
	int env_index, new_var_len;

	if (validate_env_name(name) == -1)
		return (-1);

	env_index = get_env_index(name);
	if (env_index == -1)
	{/* var doen't exist, SO CREATE IT */
		int env_count = 0;
		int old_size, new_size;

		while (__environ[env_count] != NULL)
			env_count++;

		old_size = sizeof(char *) * (env_count);
		new_size = sizeof(char *) * (env_count + 2);
		__environ = _realloc(__environ, old_size, new_size);
		if (__environ == NULL)
			dispatch_error("Error while _reallocating memory for new env var");

		/* The new value will be stored at index env_count */
		env_index = env_count;
		/* last value For the new env var needs to be NULL */
		__environ[env_count + 1] = NULL;
	}
	else
	{
		/* var exists, so overwrite it's value */
		free(__environ[env_index]);
	}

	new_var_len = _strlen(name) + _strlen(value) + 2;
	/* store the env var either if it exists or it needs to be overwritten */
	__environ[env_index] = allocate_memory(sizeof(char) * new_var_len);
	_strcpy(__environ[env_index], name);
	_strcat(__environ[env_index], "=");
	_strcat(__environ[env_index], value);

	set_process_exit_code(0);
	return (1);
}

/**
 * _unsetenv - Removes an evironment variable
 * @name: Name for the new env variable
 *
 * Return: 1 on success, -1 on error
 */
int _unsetenv(char *name)
{
	int env_index, i;

	env_index = get_env_index(name);
	if (env_index >= 0)
	{/* var exists, We can unset it */
		free(__environ[env_index]);

		for (i = env_index; __environ[i] != NULL; i++)
			__environ[i] = __environ[i + 1];

		set_process_exit_code(0);
		return (1);
	}

	/* Var doesn't exist, we can print error or do nothing */
	set_process_exit_code(0); /* Indicates that no error ocurred */

	return (1);
}
