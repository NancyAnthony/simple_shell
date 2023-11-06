#include "shell.h"

/**
 * get_history - handles the file history, get history
 * @myinfo: struct parameter
 * Return: string containing the history file
 */

char *get_history(info_t *myinfo)
{
	char *buffer, *file;

	file = get_environ(myinfo, "HOME=");
	if (!file)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_len(file)
				+ string_len(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	string_copy(buffer, file);
	string_cat(buffer, "/");
	string_cat(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * wrt_historyfile - creates a file, or appends to an existing file
 * @myinfo: the struct parameter
 *
 * Return: 1 on success, else -1
 */
int wrt_historyfile(info_t *myinfo)
{
	ssize_t fd;
	char *file_name = get_history(myinfo);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (node = myinfo->history; node; node = node->next)
	{
		_psfd(node->string, fd);
		_pfd('\n', fd);
	}
	_pfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * handles_readhistory - reads history from file
 * @myinfo: the struct parameter
 *
 * Return: his_count on success, 0 otherwise
 */
int  handles_readhistory(info_t *myinfo)
{
	int n, previous = 0, ln_count = 0;
	ssize_t fd, read_len, f_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history(myinfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (f_size + 1));
	if (!buffer)
		return (0);
	read_len = read(fd, buffer, f_size);
	buffer[f_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(fd);
	for (n = 0; n < f_size; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			handle_history_list(myinfo, buffer + previous, ln_count++);
			previous = n + 1;
		}
	if (previous != n)
		handle_history_list(myinfo, buffer + previous, ln_count++);
	free(buffer);
	myinfo->his_count = ln_count;
	while (myinfo->his_count-- >= HIST_MAX)
		handle_delete_node_index(&(myinfo->history), 0);
	renum_history(myinfo);
	return (myinfo->his_count);
}

/**
 * handle_history_list - handles entry to a history linked list
 * @myinfo: Structure containing arguments. Used to maintain the
 * linked list
 * @buffer: buffer
 * @ln_count: the history's linecount, his_count
 *
 * Return: Always 0
 */
int handle_history_list(info_t *myinfo, char *buffer, int ln_count)
{
	list_t *nod = NULL;

	if (myinfo->history)
		nod = myinfo->history;
	handle_node_end(&nod, buffer, ln_count);

	if (!myinfo->history)
		myinfo->history = nod;
	return (0);
}

/**
 * renum_history - renumbers the history list after changes have
 * been made
 * @myinfo: Structure containing potential arguments. Used to
 * maintain
 * Return: the new histcount
 */
int renum_history(info_t *myinfo)
{
	list_t *nod = myinfo->history;
	int n = 0;

	while (nod)
	{
		nod->number = n++;
		nod = nod->next;
	}
	return (myinfo->his_count = n);
}
