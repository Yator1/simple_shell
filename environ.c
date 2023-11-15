#include "main.h"

/**
 * _environ - function printing the current environment
 * @var: parameter structure containing arguments.
 *
 * Return: 0 success
 */
int _environ(vars_t *var)
{
	print_list_s(var->env);
	return (0);
}

/**
 * _get_environ - gets the char of an environ variable
 * @var: parameter structure containing arguments.
 * @name: environment name
 *
 * Return: the value
 */
char *_get_environ(vars_t *var, const char *name)
{
	list_t *node = var->env;
	char *v;

	while (node)
	{
		v = starts_with(node->str, name);
		if (v && *v)
			return (v);
		node = node->next;
	}
	return (NULL);
}

/**
  * _set_environ - function to sets environment variable.
  * @var: parameter structure.
  *
  * Return: 0 success
  */
int _set_environ(vars_t *var)
{
	if (var->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenviron(var, var->argv[1], var->argv[2]))
		return (0);
	return (1);
}

/**
 * _unset_environ - function to unset environment variable
 * @var: parameter function
 *
 *  Return: Always 0
 */
int _unset_environ(vars_t *var)
{
	int j;

	if (var->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= var->argc; j++)
		_unsetenviron(var, var->argv[j]);

	return (0);
}

/**
 * pop_environ_list- function to populate the environ linked list
 * @var: parameter structure containing arguments
 *
 * Return: Always 0
 */
int pop_environ_list(vars_t *var)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_nodeintint_end(&node, environ[n], 0);
	var->env = node;
	return (0);
}
