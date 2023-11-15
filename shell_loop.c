#include "main.h"

/**
 * shell_loop - main shell loop
 * @var: the parameter and return var struct
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int shell_loop(vars_t *var, char **av)
{
	ssize_t j = 0;
	int builtin_return = 0;
	char *prompt = "#cisfun$ ";

	while (j != -1 && builtin_return != -2)
	{
		clear_var(var);
		if (is_interactive(var))
			_puts(prompt);
		_eputchar(BUFF_FLUSH);
		j = get_input(var);
		if (j != -1)
		{
			set_var(var, av);
			builtin_return = find_builtin(var);
			if (builtin_return == -1)
				find_cmd(var);
		}
		else if (is_interactive(var))
			_putchar('\n');
		free_var(var, 0);
	}
	w_history(var);
	free_var(var, 1);
	if (!is_interactive(var) && var->status)
		exit(var->status);
	if (builtin_return == -2)
	{
		if (var->num_error == -1)
			exit(var->status);
		exit(var->num_error);
	}
	return (builtin_return);
}

/**
 * find_builtin- function to finds a builtin cmd
 * @var: parameter & return var struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(vars_t *var)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", _environ},
		{"help", _help},
		{"history", _history},
		{"setenv", _set_environ},
		{"unsetenv", _unset_environ},
		{"cd", _change_dir},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(var->argv[0], builtintbl[i].type) == 0)
		{
			var->ln_count++;
			built_in_ret = builtintbl[i].func(var);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds command in PATH
 * @var: parameter & return var structure
 *
 * Return: void
 */
void find_cmd(vars_t *var)
{
	char *path = NULL;
	int i, k;

	var->path = var->argv[0];
	if (var->ln_count_flag == 1)
	{
		var->ln_count++;
		var->ln_count_flag = 0;
	}
	for (i = 0, k = 0; var->arg[i]; i++)
		if (!is_delim(var->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _fpath(var, _get_environ(var, "PATH="), var->argv[0]);
	if (path)
	{
		var->path = path;
		fork_cmd(var);
	}
	else
	{
		if ((is_interactive(var) || _get_environ(var, "PATH=")
			|| var->argv[0][0] == '/') && is_command(var, var->argv[0]))
			fork_cmd(var);
		else if (*(var->arg) != '\n')
		{
			var->status = 127;
			_perror(var, "not found\n");
		}
	}
}

/**
 * fork_cmd- forks an exec thread to run cmd
 * @var: parameter & return var structure
 *
 * Return: void
 */
void fork_cmd(vars_t *var)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(var->path, var->argv, get_environ(var)) == -1)
		{
			free_var(var, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(var->status));
		if (WIFEXITED(var->status))
		{
			var->status = WEXITSTATUS(var->status);
			if (var->status == 126)
				_perror(var, "Permission denied\n");
		}
	}
}
