#include "main.h"

/**
 * _shellexit - exiting shell
 * @var: parameter function
 *
 * Return: exits status
 */
int _shellexit(vars_t *var)
{
	int exitcheck;

	if (var->argv[1])
	{
		exitcheck = _err_atoi(var->argv[1]);
		if (exitcheck == -1)
		{
			var->status = 2;
			_perror(var, "Ilegal number: ");
			_eputs(var->argv[1]);
			_eputchar('\n');
			return (1);
		}
		var->num_error = _err_atoi(var->argv[1]);
		return (-2);
	}
	var->num_error = -1;
	return (-2);
}

/**
 * _change_dir - function for changing directory
 * @var: parameter structure
 *
 * Return: 0 succes, 1 fail
 */
int _change_dir(vars_t *var)
{
	char *c, *directory, bufffer[1024];
	int chdir_return;

	c = getcwd(bufffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!var->argv[1])
	{
		directory = _get_environ(var, "HOME=");
		if (!directory)
			chdir_return = chdir((directory = _get_environ(var, "PWD=")
						) ? directory : "/");
		else
			chdir_return = chdir(directory);
	}
	else if (_strcmp(var->argv[1], "-") == 0)
	{
	if (!_get_environ(var, "OLDPWD="))
	{
		_puts(c);
		_putchar('\n');
		return (1);
	}
	_puts(_get_environ(var, "OLDPWD=")), _putchar('\n');
	chdir_return = /* will change this later  */
		chdir((directory = _get_environ(var, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_return = chdir(var->argv[1]);
	if (chdir_return == -1)
	{
		_perror(var, "can't cd to ");
		_eputs(var->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenviron(var, "OLDPWD", _get_environ(var, "PWD="));
		_setenviron(var, "PWD", getcwd(bufffer, 1024));
	}
	return (0);
}

/**
 * _help - help replica
 * @var: parameter structure argument
 *
 * Return: 0 success
 */
int _help(vars_t *var)
{
	char **arg_array;

	arg_array = var->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
