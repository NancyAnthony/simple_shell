#include "shell.h"

/**
 **memory_set - occupies the memory with a constant byte
 *@c: points to the memory area
 *@k: the byte that fills c
 *@d: the number of bytes to be filled
 *Return: a pointer to c
 */
char *memory_set(char *c, char k, unsigned int d)
{
	unsigned int n;

	for (n = 0; n < d; n++)
		c[n] = k;
	return (c);
}

/**
 * str_free - free a string
 * @str: string to be freed
 */
void str_free(char **str)
{
	char **s = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(s);
}

/**
 * _reallocate_mem - to handle reallocation of memory
 * @ptrs: pointer to previous block
 * @prev_size: previous block byte size
 * @recent_size: new block byte size
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocate_mem(void *ptrs, unsigned int prev_size,
unsigned int recent_size)
{
	char *b;

	if (!ptrs)
		return (malloc(recent_size));
	if (!recent_size)
		return (free(ptrs), NULL);
	if (recent_size == prev_size)
		return (ptrs);

	b = malloc(recent_size);
	if (!b)
		return (NULL);

	prev_size = prev_size < recent_size ? prev_size : recent_size;
	while (prev_size--)
		b[prev_size] = ((char *)ptrs)[prev_size];
	free(ptrs);
	return (b);
}
