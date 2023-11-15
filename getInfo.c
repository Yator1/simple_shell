#include "main.h"

/**
 * clear_var - function to clear var
 * @var: struct address
 * Return: void
 */
void clear_var(vars_t *var)
{
	var->arg = NULL;
	var->argv = NULL;
	var->path = NULL;
	var->argc = 0;
}

/**
 * set_var - function to initializes vars_t struct
 * @var: struct address
 * @av: argument vector
 *
 * Return: void
 */
void set_var(vars_t *var, char **av)
{
	int j = 0;

	var->file_name = av[0];
	if (var->arg)
	{
		var->argv = _strtok(var->arg, " \t");
		if (!var->argv)
		{

			var->argv = malloc(sizeof(char *) * 2);
			if (var->argv)
			{
				var->argv[0] = _strdup(var->arg);
				var->argv[1] = NULL;
			}
		}
		for (j = 0; var->argv && var->argv[j]; j++)
			;
		var->argc = j;

		replace_alias(var);
		replace_vars(var);
	}
}

/**
 * free_var - function to frees vars_t struct fields
 * @var: struct address
 * @all: interger to check
 */
void free_var(vars_t *var, int all)
{
	__sfree(var->argv);
	var->argv = NULL;
	var->path = NULL;
	if (all)
	{
		if (!var->cmd_buff)
			free(var->arg);
		if (var->env)
			free_list(&(var->env));
		if (var->history)
			free_list(&(var->history));
		if (var->alias)
			free_list(&(var->alias));
		__sfree(var->environ);
		var->environ = NULL;
		   _pfree((void **)var->cmd_buff);
		if (var->readfile > 2)
			close(var->readfile);
		_putchar(BUFF_FLUSH);
	}
}
