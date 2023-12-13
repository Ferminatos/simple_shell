#include "shell.h"

/**
 * allocate_memory - Manages the allocation of memory
 * @bytes: Number representing the size in bytes to allocate
 *
 * Return: Pointer to the newly allocated memory
*/
void *allocate_memory(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		dispatch_error("Error while allocating memory\n");

	return (new_mem);
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: Pointer to the memory to be reallocated
 * @old_size: Size in bytes of the actual allocated memory
 * @new_size: Size in bytes for the new allocated memory
 *
 * Return:Pointer to the newly allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	int limit, i;
	void *pointer;

	if (old_size == new_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	pointer = malloc(new_size);

	if (old_size > new_size)
		limit = new_size;
	else
		limit = old_size;

	for (i = 0; i < limit; i++)
		((char *)pointer)[i] = ((char *)ptr)[i];

	free(ptr);

	return (pointer);
}

/**
 * duplicate_string - Duplicates a given string
 * @str: String to dulicate
 *
 * Return: Pointer to the address of the newly duplicated string
*/
char *duplicate_string(char *str)
{
	char *str_copy = _strdup(str);

	if (str_copy == NULL)
		dispatch_error("Error while making copy of string");

	return (str_copy);
}

/**
 * free_dbl_ptr - Frees the memory pointed to by a double pointer
 * @dbl_ptr: Double pointer
*/
void free_dbl_ptr(char **dbl_ptr)
{
	int i;

	if (dbl_ptr == NULL)
		return;

	for (i = 0; dbl_ptr[i]; i++)
		free(dbl_ptr[i]);

	free(dbl_ptr);
}

/**
 * free_allocs - Frees allocated memory
 * @buff: Main buffer
 * @cmds_list: List of commands
 * @commands: Command as an array of arguments
 * @flags: Number indicating which memory to free
*/
void free_allocs(char *buff, char **cmds_list, char **commands, int flags)
{
	if (flags & F_BUFF)
		free(buff);
	if (flags & F_CMD_L)
		free_dbl_ptr(cmds_list);
	if (flags & F_CMDS)
		free_dbl_ptr(commands);
}
