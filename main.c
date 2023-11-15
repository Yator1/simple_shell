#include "main.h"

/**
 * main - application entry point
 * @argCount: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argCount, char **av)
{
	vars_t var[] = { VAR_INIT };
	int file_descriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (argCount == 2)
	{
		file_descriptor = open(av[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can t Open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		var->readfile = file_descriptor;
	}
	pop_environ_list(var);
	r_history(var);
	shell_loop(var, av);
	return (EXIT_SUCCESS);
}
