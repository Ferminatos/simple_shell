#include "shell.h"

/**
 * env - Prints the environment variables
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
 * _setenv - Sets an environment variable
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
	{
		int env_count = 0;
		int old_size, new_size;

		while (__environ[env_count] != NULL)
			env_count++;

		old_size = sizeof(char *) * (env_count);
		new_size = sizeof(char *) * (env_count + 2);
		__environ = _realloc(__environ, old_size, new_size);
		if (__environ == NULL)
			dispatch_error("Error while _reallocating memory for the new env var");

		env_index = env_count;
		__environ[env_count + 1] = NULL;
	}
	else
	{
		free(__environ[env_index]);
	}

	new_var_len = _strlen(name) + _strlen(value) + 2;
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
	{
		free(__environ[env_index]);

		for (i = env_index; __environ[i] != NULL; i++)
			__environ[i] = __environ[i + 1];

		set_process_exit_code(0);
		return (1);
	}

	set_process_exit_code(0);

	return (1);
}

/**
 * _cd - Changes the current directory of the process
 * @path: Path to change the working directory
 *
 * Return: 1 on success, -1 on error
*/
int _cd(char *path)
{
	char buff[1024];
	char *oldpwd;
	char *_path = path;

	if (_strcmp(path, "-") == 0)
		path = _getenv("OLDPWD");

	if (path == NULL)
	{
		print_builtin_error("cd: OLDPWD not set", "");
		return (-1);
	}
	path = duplicate_string(path);
	oldpwd = getcwd(buff, 1024);
	if (oldpwd == NULL)
	{
		free(path);
		print_builtin_error("cd: couldn't get current dir", "");
		return (-1);
	}

	if (chdir(path) == -1)
	{
		free(path);
		print_builtin_error("cd: can't change cd to ", _path);
		set_process_exit_code(1);
		return (-1);
	}
	_setenv("OLDPWD", oldpwd);
	_setenv("PWD", path);
	free(path);
	set_process_exit_code(0);
	return (1);
}

/**
 * _alias - Sets an alias
 * @commands: List of commands
 *
 * Return: -1 on error, 0 otherwise
*/
int _alias(char **commands)
{
	int status = 0;
	list_t *curr;
	list_t *out_head = NULL;
	list_t **alias_addrs = get_alias_head();

	if (commands[1] == NULL)
	{
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			_puts(curr->str);
			_puts("\n");
		}
		set_process_exit_code(0);
		return (1);
	}
	status = handle_alias_args(commands, &out_head);
	for (curr = out_head; curr != NULL; curr = curr->next)
	{
		_puts(curr->str);
		_puts("\n");
	}

	free_list(out_head);
	return (status);
}
