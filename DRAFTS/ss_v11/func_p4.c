#include "main.h"
int _strcmp(const char *s1, const char *s2)
{
	int result = 0;
	size_t len1, len2, i;
	if (s1 == NULL || s2 == NULL)
	{
		return (-1);
	}
	len1 = strlen(s1);
	len2 = strlen(s2);
	for (i = 0; i < len1 && i < len2; i++)
	{
		if (s1[i] < s2[i])
		{
			result = -1;
			break;
		}
		else
			if (s1[i] > s2[i])
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
		else
			if (len1 > len2)
			{
				result = 1;
			}
	}
	return (result);
}
