#include "shell.h"

/**
 * handling_semicolon_and_operators - Handle semicolon and logical ops
 * @buff: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void handling_semicolon_and_operators(char *buff, int read, char *first_av)
{
	char **cmds_list = NULL;

	execute_commands(buff, cmds_list, buff, read, first_av);
}

/**
 * handling_or - Handle || logical operator
 * @buff_semicolon: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * Return: 0 on success
*/
void handling_or(char *buff_semicolon, int read, char *first_av)
{
	int i, flag, prev_flag = -1;
	char **cmds_list_2 = parse_user_input(buff_semicolon, "||");

	for (i = 0; cmds_list_2[i] != NULL; i++)
	{
		flag = handling_and(cmds_list_2[i], read, first_av, prev_flag);
		prev_flag = flag;
	}
	free_dbl_ptr(cmds_list_2);
}

/**
 * handling_and - Handle && logical operator
 * @buff_or: first buffer that functions read
 * @read: return of read (open with getline)
 * @first_av: av[0]
 * @prev_flag: last flag
 * Return: 0 on success
*/
int handling_and(char *buff_or, int read, char *first_av, int prev_flag)
{
	int j = 0, flag = 1;
	char **cmds_list_3 = parse_user_input(buff_or, "&&");

	if (prev_flag == 0)
	{
		j++;
		if (cmds_list_3[j] == NULL)
			return (-1);
	}

	for (; cmds_list_3[j] != NULL; j++)
	{
		flag = execute_commands(buff_or, cmds_list_3,
					cmds_list_3[j], read, first_av);
		prev_flag = flag;
	}

	free_dbl_ptr(cmds_list_3);
	return (flag);
}
