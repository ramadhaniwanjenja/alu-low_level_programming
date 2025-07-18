#include "main.h"

/**
 * main - Entry point for function that copies the content of a file to
 * another file
 * @argc: argument counter
 * @argv: pointer to array of arguments
 * Return: 0 if succeed
 */

int main(int argc, char *argv[])
{
	int file_from, file_to;
	int reading, written;
	char buffer[1024];

	if (argc != 3)
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n"), exit(97);

	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
	{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]), exit(98);
	}

	file_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]), exit(99);
	}

	while ((reading = read(file_from, buffer, 1024)) != 0)
	{
		if (reading == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			exit(98);
		}
		written = write(file_to, buffer, reading);
		if (written == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			exit(99);
		}
	}

		if (close(file_from) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_from), exit(100);
		if (close(file_to) == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", file_to), exit(100);

		return (0);
}
