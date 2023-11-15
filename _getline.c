#include "main.h"
/**
 * input_buff- buffer inputs of chained commands
 * @var: a parameter structure
 * @buff: pointer to bufffer
 * @len: pointer to the length of var
 *
 * Return: the bytes read
 */
ssize_t input_buff(vars_t *var, char **buff, size_t *len)
{
	ssize_t bytes = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, _signhandler);
#if USE_GETLINE
		bytes = getline(buff, &len_p, stdin);
#else
		bytes = _getline(var, buff, &len_p);
#endif
		if (bytes > 0)
		{
			if ((*buff)[bytes - 1] == '\n')
			{
				(*buff)[bytes - 1] = '\0';
				bytes--;
			}
			var->ln_count_flag = 1;
			rm_comments(*buff);
			build_history(var, *buff, var->histcount++);
			{
				*len = bytes;
				var->cmd_buff = buff;
			}
		}
	}
	return (bytes);
}

/**
 * get_input- function that get the line input
 * @var: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(vars_t *var)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t b = 0;
	char **buff_p = &(var->arg), *p;

	_putchar(BUFF_FLUSH);
	b = input_buff(var, &buff, &len);
	if (b == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;

		check_chain(var, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain_delim(var, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			var->cmd_buff_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (b);
}

/**
 * read_buff - reads the size bufffer
 * @var: parameter structure
 * @buff: the bufffer
 * @i: size of buffer
 *
 * Return: the number of bytes
 */
ssize_t read_buff(vars_t *var, char *buff, size_t *i)
{
	ssize_t b = 0;

	if (*i)
		return (0);
	b = read(var->readfile, buff, READ_BUFF_SIZE);
	if (b >= 0)
		*i = b;
	return (b);
}

/**
 * _getline - function that get the input of line from stdin
 * @var: parameter struct
 * @ptr: address of pointer to bufffer
 * @length: size of preallocated pointer to bufffer
 *
 * Return: size of the input
 */
int _getline(vars_t *var, char **ptr, size_t *length)
{
	static char buff[READ_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t j = 0, l = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		l = *length;
	if (i == len)
		i = len = 0;

	j = read_buff(var, buff, &len);
	if (j == -1 || (j == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, l, l ? l + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (l)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	l += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = l;
	*ptr = p;
	return (l);
}

/**
 * _signhandler- function to handle CTRL + C
 * @sig_num: the signal number
 *
 * Return: void
 */
void _signhandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("#cisfun$");
	_putchar(BUFF_FLUSH);
}
