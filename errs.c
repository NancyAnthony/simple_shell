#include "shell.h"

/**
 *_epts -it prints an input string
 * @st: the string to be printed
 *
 * Return: Nothing
 */
void _epts(char *st)
{
	int j = 0;

	if (!st)
		return;
	while (st[j] != '\0')
	{
		eputschar(st[j]);
		j++;
	}
}

/**
 * eputschar -this writes the character c to stderr
 * @l: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int eputschar(char l)
{
	static int j;
	static char buf[WRITE_BUFF_SIZE];

	if (l == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (l != BUFF_FLUSH)
		buf[j++] = l;
	return (1);
}

/**
 * _pfd -this writes the character b to given fde
 * @b: The character to print
 * @fde: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _pfd(char b, int fde)
{
	static int j;
	static char buf[WRITE_BUFF_SIZE];

	if (b == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(fde, buf, j);
		j = 0;
	}
	if (b != BUFF_FLUSH)
		buf[j++] = b;
	return (1);
}

/**
 *_psfd -it prints an input string
 * @_str:it is the string to be printed
 * @fde:it is the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _psfd(char *_str, int fde)
{
	int j = 0;

	if (!_str)
		return (0);
	while (*_str)
	{
		j += _pfd(*_str++, fde);
	}
	return (j);
}
