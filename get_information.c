#include "shell.h"

/**
 * cleared_inf - it initializes info_t struct
 * @infor: struct address
 */
void cleared_inf(info_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}

/**
 * set_infor -it initializes info_t struct
 * @infor:the struct address
 * @v:this is the argument vector
 */
void set_infor(info_t *infor, char **v)
{
	int n = 0;

	infor->fname = v[0];
	if (infor->arg)
	{
		infor->argv = splwrd(infor->arg, " \t");
		if (!infor->argv)
		{

			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = string_dupp(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (n = 0; infor->argv && infor->argv[n]; n++)
			;
		infor->argc = n;

		rep_alias(infor);
		rep_vars(infor);
	}
}

/**
 * free_information -it frees the info_t struct fields
 * @infor: struct address
 * @f: true if freeing all the fields
 */
void free_infor(info_t *infor, int f)
{
	str_free(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (f)
	{
		if (!infor->cmd_buf)
			free(infor->arg);
		if (infor->env)
			_freelist(&(infor->env));
		if (infor->history)
			_freelist(&(infor->history));
		if (infor->alias)
			_freelist(&(infor->alias));
		str_free(infor->environ);
			infor->environ = NULL;
		be_free((void **)infor->cmd_buf);
		if (infor->read_fd > 2)
			close(infor->read_fd);
		_echar(BUFF_FLUSH);
	}
}
