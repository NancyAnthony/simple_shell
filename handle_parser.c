#include "shell.h"

/**
 * check_is_cmd - checks if a file is an executable
 * @myinfo: the info struct
 * @fp: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_is_cmd(info_t *myinfo, char *fp)
{
	struct stat stt;

	(void)myinfo;
	if (!fp || stat(fp, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_char - handles duplicate of characters
 * @path_str: the string PATH
 * @first: first index
 * @last: last index
 *
 * Return: pointer to new buffer
 */
char *duplicate_char(char *path_str, int first, int last)
{
	static char buff[1024];
	int n = 0, h = 0;

	for (h = 0, n = first; n < last; n++)
		if (path_str[n] != ':')
			buff[h++] = path_str[n];
	buff[h] = 0;
	return (buff);
}

/**
 * check_path - finds command in the PATH
 * @myinfo: the struct ifo
 * @path_str: the string, PATH
 * @command: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *check_path(info_t *myinfo, char *path_str, char *command)
{
	int n = 0, current_position = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((string_len(command) > 2) && check_start(command, "./"))
	{
		if (check_is_cmd(myinfo, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[n] || path_str[n] == ':')
		{
			path = duplicate_char(path_str, current_position, n);
			if (!*path)
				string_cat(path, command);
			else
			{
				string_cat(path, "/");
				string_cat(path, command);
			}
			if (check_is_cmd(myinfo, path))
				return (path);
			if (!path_str[n])
				break;
			current_position = n;
		}
		n++;
	}
	return (NULL);
}
