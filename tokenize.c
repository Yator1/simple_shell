#include "main.h"

/**
 * is_delim - checks for a delimeter
 * @c: char to check
 * @delim: delimeter string
 *
 * Return: 1 true, 0 false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _strtok - splits a strings into tokens.
 * @str: string
 * @d: the delimeter string
 *
 * Return: s or NULL on failure
 */

char **_strtok(char *str, char *d)
{
	int i, j, h, f, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) ||
					!str[i + 1]))
			words++;

	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words; j++)
	{
		while (is_delim(str[i], d))
			i++;
		h = 0;
		while (!is_delim(str[i + h], d) && str[i + h])
			h++;
		s[j] = malloc((h + 1) * sizeof(char));
		if (!s[j])
		{
			for (h = 0; h < j; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < h; f++)
			s[j][f] = str[i++];
		s[j][f] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_strtok2- splits strings into words
 * @str: the string
 * @d: the characters
 *
 * Return: split string
 */
char **_strtok2(char *str, char d)
{
	int x, g, h, f, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			words++;
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, g = 0; g < words; g++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		h = 0;
		while (str[x + h] != d && str[x + h] && str[x + h] != d)
			h++;
		s[g] = malloc((h + 1) * sizeof(char));
		if (!s[g])
		{
			for (h = 0; h < g; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (f = 0; f < h; f++)
			s[g][f] = str[x++];
		s[g][f] = 0;
	}
	s[g] = NULL;
	return (s);
}
