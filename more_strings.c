#include "main.h"
/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */

char *_strdup(const char *str)
{
	char *ret;
	int i, r = 0;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	for (r = 0; str[r]; r++)
		ret[r] = str[r];
	return (ret);
}
/**
 * _puts- a functions that prints a string followed by a new line
 * tp stdout
 * @str: input string
 * Return: void
 */

void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}

}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * starts_with - checks if need starts with hstack
 * @hstack: search
 * @need: to check
 * Return: addrof next char of hstack or NULL
 */
char *starts_with(const char *hstack, const char *need)
{
	while (*need)
		if (*need++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}
