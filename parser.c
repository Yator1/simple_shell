#include "main.h"

/**
 * is_command - function to check command mode
 * @path: path to the file
 * @var: parameter structure
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(vars_t *var, char *path)
{
	struct stat t;

	(void)var;
	if (!path || stat(path, &t))
		return (0);

	if (t.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * is_interactive - function to check interactive mode
 * @var: parameter structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(vars_t *var)
{
	return (isatty(STDIN_FILENO) && var->readfile <= 2);
}

/**
 * dup_char- function that duplicates characters
 * @pathstr: path to string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new bufffer
 */
char *dup_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int f = 0, g = 0;

	for (f = 0, g = start; g < stop; g++)
		if (pathstr[g] != ':')
			buff[f++] = pathstr[g];
	buff[f] = 0;
	return (buff);
}

/**
 * _fpath - finds current cmd in the PATH string
 * @var: parameter structure
 * @pathstr: path to the string
 * @cmd: the cmd to check
 *
 * Return: cmd if found or NULL
 */
char *_fpath(vars_t *var, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(var, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_char(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(var, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
