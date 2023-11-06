#include "shell.h"

/**
 * handle_list_length - handles the length of linked list
 * @l: pointer to the first node
 *
 * Return: size of list
 */
size_t handle_list_length(const list_t *l)
{
	size_t n = 0;

	while (l)
	{
		l = l->next;
		n++;
	}
	return (n);
}

/**
 * handle_list_to_str - returns an array of string to the list->string
 * @head: a pointer to first node
 *
 * Return: an array of strings
 */
char **handle_list_to_str(list_t *head)
{
	list_t *nod = head;
	size_t n = handle_list_length(head), h;
	char **strings;
	char *s;

	if (!head || !n)
		return (NULL);
	strings = malloc(sizeof(char *) * (n + 1));
	if (!strings)
		return (NULL);
	for (n = 0; nod; nod = nod->next, n++)
	{
		s = malloc(string_len(nod->string) + 1);
		if (!s)
		{
			for (h = 0; h < n; h++)
				free(strings[h]);
			free(strings);
			return (NULL);
		}

		s = string_copy(s, nod->string);
		strings[n] = s;
	}
	strings[n] = NULL;
	return (strings);
}


/**
 * handle_prnt_list - handles printing of all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t handle_prnt_list(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		get_puts(convert_no(head->number, 10, 0));
		_echar(':');
		_echar(' ');
		get_puts(head->string ? head->string : "(nil)");
		get_puts("\n");
		head = head->next;
		n++;
	}
	return (n);
}

/**
 * node_start_with_prefix - returns node whose string starts with prefix
 * @nod: the pointer to list head
 * @pre: string to be matched
 * @s: the next char after prefix
 *
 * Return: match node or null
 */
list_t *node_start_with_prefix(list_t *nod, char *pre, char s)
{
	char *d = NULL;

	while (nod)
	{
		d = check_start(nod->string, pre);
		if (d && ((s == -1) || (*d == s)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * node_index - to get the index of a node
 * @h: pointer to list head
 * @nod: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *h, list_t *nod)
{
	size_t n = 0;

	while (h)
	{
		if (h == nod)
			return (n);
		h = h->next;
		n++;
	}
	return (-1);
}
