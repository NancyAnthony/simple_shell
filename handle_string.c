#include "shell.h"

/**
 * string_len - checks and returns the length of a string
 * @c: the string to check
 *
 * Return: length of string
 */
int string_len(char *c)
{
	int n = 0;

	if (!c)
		return (0);

	while (*c++)
		n++;
	return (n);
}

/**
 * string_cmp - compares of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: -ve if str1 < str2, +v  if str1 > str2, 0 if str1 == str2
 */
int string_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * check_start - checks if needle starts with the haystack
 * @string: string to  be search
 * @substring: the substring to be found
 *
 * Return: address of next char of haystack or NULL
 */
char *check_start(const char *string, const char *substring)
{
	while (*substring)
		if (*substring++ != *string++)
			return (NULL);
	return ((char *)string);
}

/**
 * string_cat - handles concatenatin of two strings
 * @destination: the buffer destination
 * @source: the buffer source
 *
 * Return: pointer to buffer destination
 */
char *string_cat(char *destination, char *source)
{
	char *retrns = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (retrns);
}
