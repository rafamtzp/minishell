#include "libft/libft.h"
#include <stdbool.h>
#include <stdio.h>

// How to use:
// 1. have libft around
// 2. have file output.supp
// 3. run: cc -g -Ilibft supp_maker.c libft/libft.a -o supp_maker
// 4. execute ./supp_maker! :D

int main(void)
{
	bool write_mode = false;
	int fd = open("output.supp", O_RDONLY);
	int fd2 = open("supps.supp", O_APPEND | O_CREAT, 0644);
	if (fd == -1 || fd2 == -1)
	{
		printf("Error opening files\n");
		return (1);
	}
	char *line = ft_strdup("");
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line && line[0] == '{')
			write_mode = true;
		if (line && line[0] == '}')
		{
			write(fd2, "}\n", 2);
			write(fd2, "\n", 1);
			write_mode = false;
		}
		if (write_mode == true)
			dprintf(fd2, "%s", line);
	}
}