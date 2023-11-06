#include "shell.h"

/**
 * hsh - main shell loop
 * @myinfo: the parameter & return info struct
 * @arg_v: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *myinfo, char **arg_v)
{
	ssize_t h = 0;
	int builtin_return = 0;

	while (h != -1 && builtin_return != -2)
	{
		cleared_inf(myinfo);
		if (check_interactive(myinfo))
			get_puts("$ ");
		_echar(BUFF_FLUSH);
		h = _getinput(myinfo);
		if (h != -1)
		{
			set_infor(myinfo, arg_v);
			builtin_return = check_builtin(myinfo);
			if (builtin_return == -1)
				check_cmd(myinfo);
		}
		else if (check_interactive(myinfo))
			_echar('\n');
		free_infor(myinfo, 0);
	}
	wrt_historyfile(myinfo);
	free_infor(myinfo, 1);
	if (!check_interactive(myinfo) && myinfo->status)
		exit(myinfo->status);
	if (builtin_return == -2)
	{
		if (myinfo->error_num == -1)
			exit(myinfo->status);
		exit(myinfo->error_num);
	}
	return (builtin_return);
}

/**
 * check_builtin - checks for a builtin command
 * @myinfo: the parameter for inf_t & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but unsuccessful,
 *			-2 if builtin signal exit()
 */
int check_builtin(info_t *myinfo)
{
	int n, built_in_return = -1;
	builtin_table builtin_tab[] = {
		{"exit", my_exits},
		{"env", my_environ},
		{"help", _myhelper},
		{"history", handle_myhistory},
		{"setenv", myset_environ},
		{"unsetenv", my_unset_environ},
		{"cd", _cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtin_tab[n].type; n++)
		if (string_cmp(myinfo->argv[0], builtin_tab[n].type) == 0)
		{
			myinfo->line_count++;
			built_in_return = builtin_tab[n].func(myinfo);
			break;
		}
	return (built_in_return);
}

/**
 * check_cmd - checks for the command in PATH
 * @myinfo: the parameter
 *
 * Return: void
 */
void check_cmd(info_t *myinfo)
{
	char *cmd_path = NULL;
	int n, h;

	myinfo->path = myinfo->argv[0];
	if (myinfo->linecount_flag == 1)
	{
		myinfo->line_count++;
		myinfo->linecount_flag = 0;
	}
	for (n = 0, h = 0; myinfo->arg[n]; n++)
		if (!check_delimeter(myinfo->arg[n], " \t\n"))
			h++;
	if (!h)
		return;

	cmd_path = check_path(myinfo, get_environ(myinfo, "PATH="), myinfo->argv[0]);
	if (cmd_path)
	{
		myinfo->path = cmd_path;
		fork_cmd(myinfo);
	}
	else
	{
		if ((check_interactive(myinfo) || get_environ(myinfo, "PATH=")
			|| myinfo->argv[0][0] == '/') && check_is_cmd(myinfo, myinfo->argv[0]))
			fork_cmd(myinfo);
		else if (*(myinfo->arg) != '\n')
		{
			myinfo->status = 127;
			prt_err(myinfo, "cannot find file or folder\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @myinfo: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *myinfo)
{
	pid_t childpid;

	childpid = fork();
	if (childpid == -1)
	{
		/*HANDLE ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childpid == 0)
	{
		if (execve(myinfo->path, myinfo->argv, get_envy(myinfo)) == -1)
		{
			free_infor(myinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* HANDLE ERROR FUNCTION */
	}
	else
	{
		wait(&(myinfo->status));
		if (WIFEXITED(myinfo->status))
		{
			myinfo->status = WEXITSTATUS(myinfo->status);
			if (myinfo->status == 126)
				prt_err(myinfo, "Access denied\n");
		}
	}
}
