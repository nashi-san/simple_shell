#include "shell.h"

/**
 * _strncmp - Compare two strings up to a specified number of characters
 * @s1: Pointer to the first string
 * @s2: Pointer to the second string
 * @n: Maximum number of characters to compare
 * Return: Negative value if 's1' is less than 's2',
 *         0 if 's1' is equal to 's2',
 *         Positive value if 's1' is greater than 's2'
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}
/**
 * _isdigit - Check if a character is a digit
 * @c: The character to be checked
 *
 * Return: 1 if 'c' is a digit, 0 otherwise
 */
int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/**
 * _strdup - Duplicate a string
 * @str: The string to be duplicated
 *
 * Return: Pointer to the duplicated string, or NULL on failure
 */
char *_strdup(const char *str)
{
	char *dup;
	size_t len;

	if (str == NULL)
		return (NULL);

	len = _strlen(str) + 1;
	dup = malloc(len);

	if (dup == NULL)
		return (NULL);
	_memcpy(dup, str, len);

	return (dup);
}
/**
 * _strcat - Concatenate two strings
 * @dest: Destination string
 * @src: Source string
 *
 * Return: Pointer to the destination string or NULL in failure
 */
char *_strcat(char *dest, const char *src)
{
	char *ptr;

	if (dest == NULL || src == NULL)
		return (NULL);
	ptr = dest;

	while (*ptr)
		ptr++;

	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
/**
 * _strcpy - Copy a string
 * @dest: Destination string
 * @src: Source string
 *
 * Return: Pointer to the destination string nor NULL in failure
 */
char *_strcpy(char *dest, const char *src)
{
	char *ptr;

	if (dest == NULL || src == NULL)
		return (NULL);

	ptr = dest;

	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
