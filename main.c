#include "shell.h"

/**
 * main - entry point
 * @arg_c: arg count
 * @arg_v: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int arg_c, char **arg_v)
{
	info_t info[] = { INFO_INIT };
	int f_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f_d)
		: "r" (f_d));

	if (arg_c == 2)
	{
		f_d = open(arg_v[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_epts(arg_v[0]);
				_epts(": 0: Can't open ");
				_epts(arg_v[1]);
				_echar('\n');
				_echar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = f_d;
	}
	pop_environ_list(info);
	renum_history(info);
	hsh(info, arg_v);
	return (EXIT_SUCCESS);
}
