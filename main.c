#include "shell.h"

/**
 * main - Entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char**av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2:

		asm("mov %1, %0\n\t"
				"add $3, %0"
				:"=r" (fd)
				:"r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O-RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if(errno == Enoent)
		}

	}
	return (EXIT_FAILURE);
}
