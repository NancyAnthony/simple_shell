#include "shell.h"

/**
 * string_copy - to copy a string
 * @destination: the destination to be copied to
 * @source: the source to be copied from
 *
 * Return: pointer to destination
 */
char *string_copy(char *destination, char *source)
{
	int n = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[n])
	{
		destination[n] = source[n];
		n++;
	}
	destination[n] = 0;
	return (destination);
}

/**
 * string_dupp - handles duplication of a string
 * @string: the string to be duplicated
 *
 * Return: pointer to duplicated string
 */
char *string_dupp(const char *string)
{
	int len = 0;
	char *retrns;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	retrns = malloc(sizeof(char) * (len + 1));
	if (!retrns)
		return (NULL);
	for (len++; len--;)
		retrns[len] = *--string;
	return (retrns);
}

/**
 *get_puts - prints the inputted string
 *@string: the string to print
 *
 * Return: Nothing
 */
void get_puts(char *string)
{
	int n = 0;

	if (!string)
		return;
	while (string[n] != '\0')
	{
		_echar(string[n]);
		n++;
	}
}

/**
 * _echar - reads character from the STDOUT
 * @s: The character to print
 *
 * Return: 1 on success.
 * On error, returns -1, and errno is set appropriately.
 */
int _echar(char s)
{
	static int n;
	static char buffer[WRITE_BUFF_SIZE];

	if (s == BUFF_FLUSH || n >= WRITE_BUFF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (s != BUFF_FLUSH)
		buffer[n++] = s;
	return (1);
}

