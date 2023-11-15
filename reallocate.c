#include "main.h"

/**
 * _memo_set- sets file memory with a constant byte
 * @s: the pointer to memory area
 * @b: const byte
 * @n: byte in *s
 *
 * Return: s to the memory area *s
 */
char *_memo_set(char *s, char b, unsigned int n)
{
	unsigned int y;

	for (y = 0; y < n; y++)
		s[y] = b;
	return (s);
}

/**
 * __sfree - frees string
 * @pp: pointer to string
 */
void __sfree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}

/**
 * _pfree - frees a pointer
 * @ptr: address
 *
 * Return: return 1 on success otherwise 0.
 */
int _pfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _realloc - function to reallocates a block of memory
 * @ptr: pointer to mallocated block
 * @old_size: size of allocated space
 * @new_size: new size
 *
 * Return: pointer to the old block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *m;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	m = malloc(new_size);
	if (!m)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		m[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (m);
}
