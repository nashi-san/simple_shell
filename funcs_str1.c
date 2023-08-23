#include "shell.h"

/**
 * _strchr - locates a character in a string
 * @s: string
 * @c: char to locate
 * Return: first occurrence if c is found, NULL otherwise
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] >= '\0')
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
/**
 * n_conversion - converts a positive integer to a string
 * @n: positive integer
 *
 * Return: string
 */
char *n_conversion(int n)
{
	int len = 1, temp = n, i;
	char *str;

	while (temp >= 10)
	{
		len++;
		temp /= 10;
	}
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	for (i = len - 1; i >= 0; i--)
	{
		str[i] = '0' + (n % 10);
		n /= 10;
	}
	str[len] = '\0';
	return (str);
}
/**
 * _strlen - computes the length of a string
 * @str: string
 *
 * Return: length
 */
int _strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}


/**
 * _strcmp - compares two strings
 * @s1: 1st string
 * @s2: 2nd string
 *
 * Return: 0 if identical
 */
int _strcmp(char *s1, char *s2)
{
	int result = 0;
	size_t len1, len2, i;

	if (s1 == NULL || s2 == NULL)
	{
		return (-1);
	}
	len1 = _strlen(s1);
	len2 = _strlen(s2);
	for (i = 0; i < len1 && i < len2; i++)
	{
		if (s1[i] < s2[i])
		{
			result = -1;
			break;
		}
		else if (s1[i] > s2[i])
		{
			result = 1;
			break;
		}
	}
	if (result == 0)
	{
		if (len1 < len2)
		{
			result = -1;
		}
		else if (len1 > len2)
		{
			result = 1;
		}
	}
	return (result);
}

/**
 * _atoi - converts a string to an integer
 * @s: string
 *
 * Return: integer
 */
int _atoi(char *s)
{
	int i = 0, j = 0, n = 0, len = 0, k = 0, digit = 0;

	while (s[len] != '\0')
		len++;
	while (i < len && k == 0)
	{
		if (s[i] == '-')
			++j;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (j % 2)
				digit = -digit;
			n = n * 10 + digit;
			k = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			k = 0;
		}
		i++;
	}
	if (k == 0)
		return (0);
	return (n);
}
