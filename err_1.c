#include "shell.h"

/**
 * cv_str -it converts a string to an integer
 * @r: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int cv_str(char *r)
{
	int j = 0;
	unsigned long int result = 0;

	if (*r == '+')
		r++;  /* TODO: why does this make main return 255? */
	for (j = 0;  r[j] != '\0'; j++)
	{
		if (r[j] >= '0' && r[j] <= '9')
		{
			result *= 10;
			result += (r[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prt_err -it prints an error message
 * @infor:it is the parameter & return info struct
 * @err_str:it is a string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void prt_err(info_t *infor, char *err_str)
{
	_epts(info->fname);
	_epts(": ");
	print_de(info->line_count, STDERR_FILENO);
	_epts(": ");
	_epts(info->argv[0]);
	_epts(": ");
	_epts(estr);
}

/**
 * print_de -a function prints a decimal (integer) number (base 10)
 * @inputs:it is the input
 * @fde: the filedescriptor to write to
 *
 * Return: number of characters that is printed
 */
int print_de(int inputs, int fde)
{
	int (*__putchar)(char) = _echar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fde == STDERR_FILENO)
		__putchar = eputschar;
	if (inputs < 0)
	{
		_abs_ = -inputs;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inputs;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_no -a converter function, the clone of itoa
 * @no: number
 * @ba:the base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_no(long int no, int ba, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long u = no;

	if (!(flags & CONVERT_UNSIGNED) && no < 0)
	{
		u = -no;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[u % ba];
		u /= ba;
	} while (u != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments -the function replaces the first instance of '#' with '\0'
 * @buff:the address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
