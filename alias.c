#include "main.h"
/**
 * _history - disqlays the history
 * @var: the parameter structure.
 *
 * Return: 0 on success, 1 failure
 */
int _history(vars_t *var)
{
	print_list(var->history);
	return (0);
}

/**
 * unset_alias - function to unsets alias
 * @var: parameter structure
 * @str: alias string
 *
 * Return: 0 on success, 1 on failure
 */
int unset_alias(vars_t *var, char *str)
{
	char *m, n;
	int ret;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	n = *m;
	*m = 0;
	ret = delete_node_at_index(&(var->alias),
		get_node_index(var->alias, node_starts_with(var->alias, str, -1)));
	*m = n;
	return (ret);
}

/**
 * set_alias - function to sets alias
 * @var: parameter structure
 * @str: alias string
 *
 * Return: 0 success, 1 failed
 */
int set_alias(vars_t *var, char *str)
{
	char *t;

	t = _strchr(str, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (unset_alias(var, str));

	unset_alias(var, str);
	return (add_nodeintint_end(&(var->alias), str, 0) == NULL);
}

/**
 * print_alias - function to prints alias
 * @node: alias node
 *
 * Return: 0 success, 1 failure
 */
int print_alias(list_t *node)
{
	char *d = NULL, *a = NULL;

	if (node)
	{
		d = _strchr(node->str, '=');
		for (a = node->str; a <= d; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(d + 1);
		      _puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - replica of the alias builtin
 * @var: Structure containing
 *
 * Return: 0 success, -1 failure
 */
int _alias(vars_t *var)
{
	int i = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (var->argc == 1)
	{
		node = var->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; var->argv[i]; i++)
	{
		b = _strchr(var->argv[i], '=');
		if (b)
			set_alias(var, var->argv[i]);
		else
			print_alias(node_starts_with(var->alias, var->argv[i], '='));
	}

	return (0);
}
