#include "main.h"
/**
 * read_textfile - read a certain size and prints to std output
 * @filename: file to read from
 * @letters: size to read
 * Return: actual size read and printed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd, read_no, write_no;
	char *buffer;

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buffer = malloc(sizeof(char) * letters);
	if (buffer == NULL)
		return (0);

	read_no = read(fd, buffer, letters);
	if (read_no == -1)
	{
		free(buffer);
		close(fd);
		return (0);
	}

	write_no = write(STDOUT_FILENO, buffer, read_no);
	if (write_no == -1)
	{
		free(buffer);
		close(fd);
		return (0);
	}

	close(fd);
	return (read_no);
}
