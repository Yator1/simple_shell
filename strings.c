#include"main.h"

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _strlen(char *s)- a function that returns the length of a string
 * @s: string variable
 * Return: length
 */
int _strlen(char *s)
{
	int length = 0;

	while (s[length] != '\0')
		length++;
	return (length);
}
/**
* _strncpy - functions that copies a string.
* @dest: destination string pointer
* @src: source string pointer
* @n: number of bytes to be used
* Return: destination pointer
*/

char *_strncpy(char *dest, char *src, int n)
{
	int bytesCount;

	for (bytesCount = 0; bytesCount < n && src[bytesCount] != '\0'; bytesCount++)
	{
		dest[bytesCount] = src[bytesCount];
	}
	for (; bytesCount < n; bytesCount++)
	{
		dest[bytesCount] = '\0';
	}
	return (dest);
}
/**
* _strncat- function that concatenates two strings.
* @dest: destination string pointer
* @src: source string pointer
* @n: number of bytes to be concatenated.
* Return: destination string pointer
*/
char *_strncat(char *dest, char *src, int n)
{
	int len, z;

	len = 0;
	while (dest[len] != '\0')
	{
		len++;
	}
	for (z = 0; z < n && src[z] != '\0'; z++, len++)
	{
		dest[len] = src[z];
	}
	dest[len] = '\0';
	return (dest);
}
/**
* *_strchr- function that locates a character in a string
* @s: pointer to the string
* @c: the character to be located.
* Return: if c is found, a pointer to the first occurence
* if c is not found, NULL
*/
char *_strchr(char *s, char c)
{
	int n;

	for (n = 0; s[n] >= '\0'; n++)
	{
		if (s[n] == c)
			return (s + n);
	}
	return ('\0');
}
