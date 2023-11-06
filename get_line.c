#include "shell.h"

/**
 * chain_buff - buffers the chained commands
 * @myinfo: the parameter struct
 * @buffer: buffer address
 * @length: the address of length
 *
 * Return: bytes read
 */
ssize_t chain_buff(info_t *myinfo, char **buffer, size_t *length)
{
	ssize_t t = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing there is left in the buffer, occupy it */
	{
		/*be_free((void **)info->cmd_buff);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buffer, &length_p, stdin);
#else
		t = get_line(myinfo, buffer, &length_p);
#endif
		if (t > 0)
		{
			if ((*buffer)[t - 1] == '\n')
			{
				(*buffer)[t - 1] = '\0'; /* removes any trailing newline */
				t--;
			}
			myinfo->linecount_flag = 1;
			rm_comments(*buffer);
			handle_history_list(myinfo, *buffer, myinfo->his_count++);
			/* if (st_ch(*buf, ';')) this a command chain? */
			{
				*length = t;
				myinfo->cmd_buf = buffer;
			}
		}
	}
	return (t);
}

/**
 * _getinput - gets a line minus the newline
 * @myinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t _getinput(info_t *myinfo)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t n, k, length;
	ssize_t rd = 0;
	char **buff_d = &(myinfo->arg), *d;

	putchar(BUFF_FLUSH);
	rd = chain_buff(myinfo, &buffer, &length);
	if (rd == -1) /* EOF */
		return (-1);
	if (length)	/* commands left in the chain buffer */
	{
		k = n; /* initialize new iterator to current buffer position */
		d = buffer + n; /* get pointer to return */

		handles_chain(myinfo, buffer, &k, n, length);
		while (k < length) /* iterate to semicolon or end */
		{
			if (check_ischain(myinfo, buffer, &k))
				break;
			k++;
		}

		n = k + 1; /* past null incremented ';'' */
		if (n >= length) /* buffer end? */
		{
			n = length = 0; /* reset the position and length */
			myinfo->cmd_buf_type = CMD_NORM;
		}

		*buff_d = d; /* passes pointer to current cmd position */
		return (string_len(d)); /* return length of current command */
	}

	*buff_d = buffer; /* else not a chain, pass back buffer from get_lines */
	return (rd); /* return length of buffer from get_lines*/
}

/**
 * rd_buff - to handle reading a buffer
 * @myinfo: the parameter struct
 * @buffer: the buffer
 * @n: the size
 *
 * Return: rd
 */
ssize_t rd_buff(info_t *myinfo, char *buffer, size_t *n)
{
	ssize_t rd = 0;

	if (*n)
		return (0);
	rd = read(myinfo->read_fd, buffer, READ_BUFF_SIZE);
	if (rd >= 0)
		*n = rd;
	return (rd);
}

/**
 * get_line - gets the next line of input
 * @myinfo: the parameter struct
 * @p: pointer to buffer, either preallocated or NULL
 * @len: size of the preallocated p buffer, if not NULL
 *
 * Return: s
 */
int get_line(info_t *myinfo, char **p, size_t *len)
{
	static char buff[READ_BUFF_SIZE];
	static size_t n, l;
	size_t h;
	ssize_t v = 0, d = 0;
	char *ptr = NULL, *new_ptr = NULL, *p_s;

	ptr = *p;
	if (ptr && len)
		d = *len;
	if (n == l)
		n = l = 0;

	v = rd_buff(myinfo, buff, &l);
	if (v == -1 || (v == 0 && len == 0))
		return (-1);

	p_s = strchr(buff + n, '\n');
	h = p_s ? 1 + (unsigned int)(p_s - buff) : l;
	new_ptr = _reallocate_mem(ptr, d, d ? d + h : h + 1);
	if (!new_ptr) /* MALLOC FAILS! */
		return (ptr ? free(ptr), -1 : -1);

	if (d)
		str_cat(new_ptr, buff + n, h - n);
	else
		_strcp(new_ptr, buff + n, h - n + 1);

	d += h - n;
	n = h;
	ptr = new_ptr;

	if (len)
		*len = d;
	*p = ptr;
	return (d);
}

/**
 * sigintHandler - blocks the use ctrl-C
 * @signum: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signum)
{
	get_puts("\n");
	get_puts("$ ");
	putchar(BUFF_FLUSH);
}
