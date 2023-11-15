#include "main.h"

/**
 * _err_atoi - converts a string to an integer, _atoi
 * @s: string to be converted
 *
 * Return: the number, or -1 fail
 */
int _err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * _print_dec - function that prints decimal numbers
 * @input: input
 * @fd: the file descriptor
 *
 * Return: number of characters printed
 */
int _print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, ct = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			ct++;
		}
		current %= i;
	}
	__putchar('0' + current);
	ct++;

	return (ct);
}

/**
 * _itoa - converts int to other base, clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *_itoa(long int num, int base, int flags)
{
	static char *ar;
	static char bufffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	ar = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &bufffer[49];
	*ptr = '\0';

	do	{
		*--ptr = ar[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - function for ignoring comments
 * @buff: address to string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}

/**
 * _perror - prints error message to stdout
 * @var: parameters structure
 * @estr: string containing error
 *
 * Return: 0 if converted number otherwise, -1 on error
 */
void _perror(vars_t *var, char *estr)
{
	_eputs(var->file_name);
	    _eputs(": ");
	     _print_dec(var->ln_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(var->argv[0]);
	    _eputs(": ");
	_eputs(estr);
}
