#include "main.h"

/**
 * find_history - gets file history
 * @var: parameter structure
 *
 * Return: allocated string
 */

char *find_history(vars_t *var)
{
	char *buff, *dir;

	dir = _get_environ(var, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * w_history - writes the history
 * @var: parameter struct
 *
 * Return: 1 success, else -1
 */
int w_history(vars_t *var)
{
	ssize_t fd;
	char *filename = find_history(var);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = var->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r_history - reads history of a file
 * @var: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int r_history(vars_t *var)
{
	int i, hist = 0, linec = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = find_history(var);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history(var, buff + hist, linec++);
			hist = i + 1;
		}
	if (hist != i)
		build_history(var, buff + hist, linec++);
	free(buff);
	var->histcount = linec;
	while (var->histcount-- >= HIST_MAX)
		delete_node_at_index(&(var->history), 0);
	renum_history(var);
	return (var->histcount);
}

/**
 * build_history - function to build history of linked list
 * @var: parameter argument.
 * @buff: bufffer
 * @linecount: history linecount
 *
 * Return: Always 0
 */
int build_history(vars_t *var, char *buff, int linecount)
{
	list_t *node = NULL;

	if (var->history)
		node = var->history;
	add_nodeintint_end(&node, buff, linecount);

	if (!var->history)
		var->history = node;
	return (0);
}

/**
 * renum_history - function to renumbers the list after changes
 * @var: Struct of potential arguments.
 *
 * Return: the number
 */
int renum_history(vars_t *var)
{
	list_t *node = var->history;
	int p = 0;

	while (node)
	{
		node->num = p++;
		node = node->next;
	}
	return (var->histcount = p);
}
