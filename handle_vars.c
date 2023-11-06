#include "shell.h"

/**
 * check_ischain - checks if current character in buffer is a chain delimeter
 * @myinfo: the parameter struct
 * @buffer: the character buffer
 * @s: address position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_ischain(info_t *myinfo, char *buffer, size_t *s)
{
	size_t i = *s;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		myinfo->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		myinfo->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';') /* found end of this command */
	{
		buffer[i] = 0; /* replace semicolon with null */
		myinfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*s = i;
	return (1);
}

/**
 * handles_chain - handles chain based on the previous status
 * @myinfo: the parameter struct
 * @buffer: the character buffer
 * @s: the address of the position in buf
 * @n: starting position in buffer
 * @buff_len: length of buf
 *
 * Return: Void
 */
void handles_chain(info_t *myinfo, char *buffer, size_t *s, size_t n,
size_t buff_len)
{
	size_t d = *s;

	if (myinfo->cmd_buf_type == CMD_AND)
	{
		if (myinfo->status)
		{
			buffer[n] = 0;
			d = buff_len;
		}
	}
	if (myinfo->cmd_buf_type == CMD_OR)
	{
		if (!myinfo->status)
		{
			buffer[n] = 0;
			d = buff_len;
		}
	}

	*s = d;
}

/**
 * rep_alias - replaces alias in the tokenized string
 * @myinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *myinfo)
{
	int n;
	list_t *nod;
	char *s;

	for (n = 0; n < 10; n++)
	{
		nod = node_start_with_prefix(myinfo->alias, myinfo->argv[0], '=');
		if (!nod)
			return (0);
		free(myinfo->argv[0]);
		s = st_ch(nod->string, '=');
		if (!s)
			return (0);
		s = string_dupp(s + 1);
		if (!s)
			return (0);
		myinfo->argv[0] = s;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @myinfo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *myinfo)
{
	int n = 0;
	list_t *nod;

	for (n = 0; myinfo->argv[n]; n++)
	{
		if (myinfo->argv[n][0] != '$' || !myinfo->argv[n][1])
			continue;

		if (!string_cmp(myinfo->argv[n], "$?"))
		{
			rep_str(&(myinfo->argv[n]),
				string_dupp(convert_no(myinfo->status, 10, 0)));
			continue;
		}
		if (!string_cmp(myinfo->argv[n], "$$"))
		{
			rep_str(&(myinfo->argv[n]),
				string_dupp(convert_no(getpid(), 10, 0)));
			continue;
		}
		nod = node_start_with_prefix(myinfo->env, &myinfo->argv[n][1], '=');
		if (nod)
		{
			rep_str(&(myinfo->argv[n]),
				string_dupp(st_ch(nod->string, '=') + 1));
			continue;
		}
		rep_str(&myinfo->argv[n], string_dupp(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @outdated: address of old str
 * @updated: the new new str
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **outdated, char *updated)
{
	free(*outdated);
	*outdated = updated;
	return (1);
}
