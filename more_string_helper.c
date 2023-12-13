#include "shell.h"

/**
 * _strchr - string searching
 * @s: string 1
 * @c: character to search
 * Return: return a pointer to the byte, or
 * a null pointer if the byte was not found.
 */
char *_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}

/**
 * _strcat - concatenate two strings
 * @s1: string 1
 * @s2: string 2
 * Return: return a pointer to the resulting string dest.
 */
char *_strcat(char *s1, const char *s2)
{
	return (_strncat(s1, s2, -1));
}

/**
 * _strncat - concatenate first n chars of s2 to s1 string
 * @s1: string 1
 * @s2: string 2
 * @n: numbers of characters of s2 to concatenate to the s1
 * Return: return a pointer to the resulting string dest.
 */
char *_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = _strlen(s1);
	j = 0;
	while (s2[j] && j < n)
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}

/**
 * _strcpy - Copies the string src to dest
 * @dest: String destination
 * @src: String source
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	char *mem_address;

	mem_address = dest;

	while (*src != '\0')
	{
		*mem_address = *src;
		mem_address++;
		src++;
	}
	*mem_address = '\0';

	return (dest);
}

/**
 * _strncpy - Copies n number chars of a string
 * @dest: String destination
 * @src: String source
 * @n: Number of chars to copy from src
 * Return: Pointer to dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int count = 0;
	char *start = dest;

	while (*src != '\0' && count < n)
	{
		*(start++) = *(src++);
		count++;
	}

	while (count < n)
	{
		*(start++) = '\0';
		count++;
	}

	return (dest);
}
