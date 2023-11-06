#include "shell.h"

/**
 * my_exits -  this exists the shell
 * @a: The structure that contains potential arguments.
 * it is used to maintain constant function prototype
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int my_exits(info_t *a)
{
	int exit;

	if (a->argv[1]) /* If it is an exit arguement */
	{
		exit = cv_str(a->argv[1]);
		if (exit == -1)
		{
			a->status = 2;
			prt_err(a, "Illegal number: ");
			_epts(a->argv[1]);
			eputschar('\n');
			return (1);
		}
		a->error_num = cv_str(a->argv[1]);
		return (-2);
	}
	a->error_num = -1;
	return (-2);
}
/**
 * _cd - Changes the current working directory
 * @s: It is a structure that contains the potential arguments.
 * It is used to maintain constant function prototype.
 * Return: Always 0
 */
int _cd(info_t *s)
{
	char *n, *dirt, buffer[1024];
	int chdir_rit;

	n = getcwd(buffer, 1024);
	if (!n)
		puts("TODO: >>getcwd failure emsg here<<\n");
	if (!s->argv[1])
	{
		dirt = get_environ(s, "HOME=");
		if (!dirt)
			chdir_rit = /* TODO: what should this be? */
				chdir((dirt = get_environ(s, "PWD=")) ? dirt : "/");
		else
			chdir_rit = chdir(dirt);
	}
	else if (strcmp(s->argv[1], "-") == 0)
	{
		if (!get_environ(s, "OLDPWD="))
		{
			puts(n);
			_echar('\n');
			return (1);
		}
		puts(get_environ(s, "OLDPWD=")), _echar('\n');
		chdir_rit = /* what should this handle? */
			chdir((dirt = get_environ(s, "OLDPWD=")) ? dirt : "/");
	}
	else
		chdir_rit = chdir(s->argv[1]);
	if (chdir_rit == -1)
	{
		prt_err(s, "can't cd to ");
		_epts(s->argv[1]), eputschar('\n');
	}
	else
	{
		set_env(s, "OLDPWD", get_environ(s, "PWD="));
		set_env(s, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelper -it changes the process of the current directory
 *@i: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelper(info_t *i)
{
	char **arg_array;

	arg_array = i->argv;
	puts("help call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
