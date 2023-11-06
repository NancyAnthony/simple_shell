#include "shell.h"

/**
 * handle_addnode - adds a node to the start of the list
 * @head: pointer to head node
 * @string: string of node
 * @number: index in history
 *
 * Return: size of list
 */
list_t *handle_addnode(list_t **head, const char *string, int number)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memory_set((void *)new_head, 0, sizeof(list_t));
	new_head->number = number;
	if (string)
	{
		new_head->string = string_dupp(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * handle_node_end - handles adding a node to the end of the list
 * @head: pointer to head node
 * @string: string of node
 * @number: index used in history
 *
 * Return: list size
 */
list_t *handle_node_end(list_t **head, const char *string, int number)
{
	list_t *new_nod, *nod;

	if (!head)
		return (NULL);

	nod = *head;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	memory_set((void *)new_nod, 0, sizeof(list_t));
	new_nod->number = number;
	if (string)
	{
		new_nod->string = string_dupp(string);
		if (!new_nod->string)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * print_string - prints the string element of the list_t
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_string(const list_t *head)
{
	size_t n = 0;

	while (head)
	{
		get_puts(head->string ? head->string : "(nil)");
		get_puts("\n");
		head = head->next;
		n++;
	}
	return (n);
}

/**
 * handle_delete_node_index - handles deletion of node at given index
 * @head: pointer to first node
 * @indexes: index of node to be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int handle_delete_node_index(list_t **head, unsigned int indexes)
{
	list_t *nod, *previous_nod;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);

	if (!indexes)
	{
		nod = *head;
		*head = (*head)->next;
		free(nod->string);
		free(nod);
		return (1);
	}
	nod = *head;
	while (nod)
	{
		if (n == indexes)
		{
			previous_nod->next = nod->next;
			free(nod->string);
			free(nod);
			return (1);
		}
		n++;
		previous_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * _freelist - frees all the list nodes
 * @head_p: pointer to head node
 * Return: void
 */
void _freelist(list_t **head_p)
{
	list_t *nod, *next_nod, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	nod = head;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->string);
		free(nod);
		nod = next_nod;
	}
	*head_p = NULL;
}
