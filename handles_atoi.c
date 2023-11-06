#include "shell.h"

/**
 * check_interactive - if shell is interactive mode, returns true
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * check_delimeter - To checks if char is a delimeter
 * @s: the character to check
 * @del: the delimeter string to check
 * Return: 1 if true, 0 if false
 */
int check_delimeter(char s, char *del)
{
	while (*del)
		if (*del++ == s)
			return (1);
	return (0);
}

/**
 *check_isalpha - handles checks for alphabetic char
 *@s: The char input
 *Return: 1 if s is alphabetic, 0 otherwise
 */

int check_isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *handle_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int handle_atoi(char *str)
{
	int n, sign = 1, flag = 0, output;
	unsigned int outcome = 0;

	for (n = 0;  str[n] != '\0' && flag != 2; n++)
	{
		if (str[n] == '-')
			sign *= -1;

		if (str[n] >= '0' && str[n] <= '9')
		{
			flag = 1;
			outcome *= 10;
			outcome += (str[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -outcome;
	else
		output = outcome;

	return (output);
}
