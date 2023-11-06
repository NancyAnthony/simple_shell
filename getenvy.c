#include "shell.h"

/**
 * get_envy -this returns the string array copy of our environ
 * @information:The Structure containing potential arguments
 * Return: Always 0
 */
char **get_envy(info_t *information)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = handle_list_to_str(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * unset_env - Remove an environment variable
 * @inf: Structure containing potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @vary:it is the string env var property
 */
int unset_env(info_t *inf, char *vary)
{
	list_t *node = inf->env;
	size_t n = 0;
	char *m;

	if (!node || !vary)
		return (0);

	while (node)
	{
		m = check_start(node->string, vary);
		if (m && *m == '=')
		{
			inf->env_changed = handle_delete_node_index(&(inf->env), n);
			n = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (inf->env_changed);
}

/**
 * set_env -It Initializes a new environment variable,
 *             or modifies an existing one
 * @inf:The Structure containing potential arguments.It is Used to maintain
 *        constant function prototype.
 * @vary: string env var property
 * @values: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *inf, char *vary, char *values)
{
	char *buff = NULL;
	list_t *nodes;
	char *m;

	if (!vary || !values)
		return (0);

	buff = malloc(string_len(vary) + string_len(values) + 2);
	if (!buff)
		return (1);
	string_copy(buff, vary);
	string_cat(buff, "=");
	string_cat(buff, values);
	nodes = inf->env;
	while (nodes)
	{
		m = check_start(nodes->string, vary);
		if (m && *m == '=')
		{
			free(nodes->string);
			nodes->string = buff;
			inf->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	handle_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
