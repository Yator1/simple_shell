#include"main.h"
/**
 * _isalpha-checks for alphabetic charracters
 * @c: the character to be checked
 * Return: 1 if c is the character, otherwise return 0
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/**
* _strcmp- a functions that compares two strings
* @s1: first string pointer
* @s2: second string pointer
* Return: value < 0 if s1 is < s2 and value > 0 if s1 > s2
* value == 0 if s1 = s2
*/

int _strcmp(char *s1, char *s2)
{
	int n, results;

	n = 0;
	while (s1[n] == s2[n] && s1[n] != '\0')
	{
		n++;
	}
	results = s1[n] - s2[n];
	return (results);
}
/**
* _strcat - function that concatenates two strings.
* @dest: pointer to the destination string
* @src: pointer to the source string
* Return: pointer to the destination string
*/
char *_strcat(char *dest, char *src)
{
	int length_of_string, z;

	length_of_string = 0;
	while (dest[length_of_string] != '\0')
	{
		length_of_string++;
	}
	for (z = 0; src[z] != '\0'; z++, length_of_string++)
	{
		dest[length_of_string] = src[z];
	}
	dest[length_of_string] = '\0';
	return (dest);
}

/**
 * *_strcpy-copies the string to dest by a src
 * @dest: pointer to a char type string destination
 * @src: pointer to a char type string source
 * Return: a cahr pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int j = -1;

	do {
		j++;
		dest[j] = src[j];
	} while (src[j] != '\0');

	return (dest);
}
