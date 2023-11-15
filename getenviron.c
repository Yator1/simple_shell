#include "main.h"

/**
 * get_environ - function to get enviroment.
 * @var: parameter structure containing argument.
 *
 * Return: 0 success
 */
char **get_environ(vars_t *var)
{
	if (!var->environ || var->envi_change)
	{
		var->environ = list_to_strings(var->env);
		var->envi_change = 0;
	}

	return (var->environ);
}

/**
 * _unsetenviron - function remove an environment variable
 * @var: parameter structure containing potential arguments
 * @c: the string
 *
 * Return: 0 success
 */
int _unsetenviron(vars_t *var, char *c)
{
	list_t *node = var->env;
	int i = 0;
	char *r;

	if (!node || !c)
		return (0);

	while (node)
	{
		r = starts_with(node->str, c);
		if (r && *r == '=')
		{
			var->envi_change = delete_node_at_index(&(var->env), i);
			i = 0;
			node = var->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (var->envi_change);
}

/**
 * _setenviron - function to init a new envi variable or modify an existing one
 * @var: parameter structure
 * @value: the string env var value
 * @c: the string env var property
 *
 * Return: 0 success
 */
int _setenviron(vars_t *var, char *c, char *value)
{
	char *bufffer = NULL;
	list_t *node;
	char *n;

	if (!c || !value)
		return (0);

	bufffer = malloc(_strlen(c) + _strlen(value) + 2);
	if (!bufffer)
		return (1);
	_strcpy(bufffer, c);
	_strcat(bufffer, "=");
	_strcat(bufffer, value);
	node = var->env;
	while (node)
	{
		n = starts_with(node->str, c);
		if (n && *n == '=')
		{
			free(node->str);
			node->str = bufffer;
			var->envi_change = 1;
			return (0);
		}
		node = node->next;
	}
	add_nodeintint_end(&(var->env), bufffer, 0);
	free(bufffer);
	var->envi_change = 1;
	return (0);
}
