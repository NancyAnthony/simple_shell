#include "shell.h"

/**
 * my_environ - prints the current environment
 * @myinfo: Structure containing potential arguments for maintaining
 *          constant function prototype.
 * Return: Always 0
 */
int my_environ(info_t *myinfo)
{
	print_string(myinfo->env);
	return (0);
}

/**
 * get_environ - gets the value of an environment variable
 * @myinfo: Structure containing potential arguments
 * @n: environment name
 *
 * Return: the value
 */
char *get_environ(info_t *myinfo, const char *n)
{
	list_t *nod = myinfo->env;
	char *d;

	while (nod)
	{
		d = check_start(nod->string, n);
		if (d && *d)
			return (d);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * myset_environ - Initializes a new environment variable,
 *             or modify an existing one
 * @myinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int myset_environ(info_t *myinfo)
{
	if (myinfo->argc != 3)
	{
		_epts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(myinfo, myinfo->argv[1], myinfo->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_environ - Remove an environment variable
 * @myinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_unset_environ(info_t *myinfo)
{
	int i;

	if (myinfo->argc == 1)
	{
		_epts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= myinfo->argc; i++)
		unset_env(myinfo, myinfo->argv[i]);

	return (0);
}

/**
 * pop_environ_list - populates enviroment linked list
 * @myinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_environ_list(info_t *myinfo)
{
	list_t *nod = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		handle_node_end(&nod, environ[i], 0);
	myinfo->env = nod;
	return (0);
}
