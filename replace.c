#include "main.h"

/**
 * is_chain_delim - test if char is chain delimeter
 * @var: parameter structure
 * @buff: pointer to bufffer
 * @p: pointer to address
 *
 * Return: 1 if delimeter, 0 otherwise
 */
int is_chain_delim(vars_t *var, char *buff, size_t *p)
{
	size_t f = *p;

	if (buff[f] == '|' && buff[f + 1] == '|')
	{
		buff[f] = 0;
		f++;
		var->cmd_buff_type = CMD_OR;
	}
	else if (buff[f] == '&' && buff[f + 1] == '&')
	{
		buff[f] = 0;
		f++;
		var->cmd_buff_type = CMD_AND;
	}
	else if (buff[f] == ';')
	{
		buff[f] = 0;
		var->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = f;
	return (1);
}

/**
 * check_chain- checks if to continue chaining
 * @var: parameter structure
 * @buff: pointer to bufffer
 * @p: address of current pos in buff
 * @i: bytes
 * @len: length of buff
 *
 * Return: x
 */
void check_chain(vars_t *var, char *buff, size_t *p, size_t i, size_t len)
{
	size_t f = *p;

	if (var->cmd_buff_type == CMD_AND)
	{
		if (var->status)
		{
			buff[i] = 0;
			f = len;
		}
	}
	if (var->cmd_buff_type == CMD_OR)
	{
		if (!var->status)
		{
			buff[i] = 0;
			f = len;
		}
	}

	*p = f;
}

/**
 * replace_alias - replaces an aliases
 * @var: the parameter structure
 *
 * Return: 1 success, 0 otherwise
 */
int replace_alias(vars_t *var)
{
	int i;
	list_t *node;
	char *c;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(var->alias, var->argv[0], '=');
		if (!node)
			return (0);
		free(var->argv[0]);
		c = _strchr(node->str, '=');
		if (!c)
			return (0);
		c = _strdup(c + 1);
		if (!c)
			return (0);
		var->argv[0] = c;
	}
	return (1);
}

/**
 * replace_vars- function to replaces vars in the tokenized string
 * @var: parameter structure
 *
 * Return: 1 success, 0 otherwise
 */
int replace_vars(vars_t *var)
{
	int i = 0;
	list_t *node;

	for (i = 0; var->argv[i]; i++)
	{
		if (var->argv[i][0] != '$' || !var->argv[i][1])
			continue;

		if (!_strcmp(var->argv[i], "$?"))
		{
			replace_string(&(var->argv[i]),
				_strdup(_itoa(var->status, 10, 0)));
			continue;
		}
		if (!_strcmp(var->argv[i], "$$"))
		{
			replace_string(&(var->argv[i]),
				_strdup(_itoa(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(var->env, &var->argv[i][1], '=');
		if (node)
		{
			replace_string(&(var->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&var->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @current: current string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *current)
{
	free(*old);
	*old = current;
	return (1);
}
