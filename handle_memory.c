#include "shell.h"

/**
 * be_free - frees the pointer and NULLs the address of the pointer
 * @p: pointer to free
 *
 * Return: 1 if free, otherwise 0.
 */
int be_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
