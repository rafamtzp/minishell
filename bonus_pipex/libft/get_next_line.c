/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:22:44 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/06 11:35:18 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*freebuf(char **ptr)
{
	if (*ptr != NULL && ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*setline(char *linebuf)
{
	char			*leftovers;
	unsigned int	l;

	while (*linebuf != '\n' && *linebuf)
		linebuf++;
	if (*linebuf == '\n')
		linebuf++;
	l = ft_strlen(linebuf);
	leftovers = ft_calloc(1, l + 1);
	if (!leftovers)
		return (NULL);
	l = 0;
	while (linebuf[l])
	{
		leftovers[l] = linebuf[l];
		l++;
	}
	*linebuf = '\0';
	return (leftovers);
}

static char	*appendbufs(int fd, char *buffer, char *leftovers)
{
	char	*tmp;
	int		bytesread;

	bytesread = BUFFER_SIZE;
	while (bytesread == BUFFER_SIZE && ft_strchr(buffer, '\n') == NULL)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (NULL);
		else if (bytesread == 0)
			break ;
		if (!leftovers)
			leftovers = ft_strdup("");
		tmp = leftovers;
		buffer[bytesread] = '\0';
		leftovers = ft_strjoin(tmp, buffer);
		freebuf(&tmp);
		if (!leftovers)
			return (NULL);
	}
	return (leftovers);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*linebuf;
	static char	*leftovers;

	linebuf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (freebuf(&leftovers));
	buffer = ft_calloc(1, BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	linebuf = appendbufs(fd, buffer, leftovers);
	freebuf(&buffer);
	if (!linebuf)
		return (freebuf(&leftovers));
	leftovers = setline(linebuf);
	if (!leftovers)
		freebuf(&linebuf);
	else if (*leftovers == '\0')
		freebuf(&leftovers);
	return (linebuf);
}

/*
MAIN BUENO:
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	char *linebuf;
	int fd = open("read_error.txt", O_RDONLY);
	
	linebuf = get_next_line(fd);
	printf("linea 1: %s", linebuf);
	free(linebuf);
	
	close(fd);
	linebuf = get_next_line(fd);
	printf("linea 2: %s", linebuf);
	//free(linebuf);

	linebuf = get_next_line(fd);
	printf("linea 3: %s", linebuf);
	//free(linebuf);
}
*/	

/*#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char *linebuf;
	int fd = open("read_error.txt", O_RDONLY);
    if (fd < 0)
        {close(fd);}
	for (int i = 1; i <= 5; i++)
	{
		linebuf = get_next_line(fd);
		printf("%s", linebuf);
		free(linebuf);
	}
	linebuf = get_next_line(fd);
	printf("%s", linebuf);
	free(linebuf);
	close(fd);
	fd = open("read_error.txt", O_RDONLY);
    if (fd < 0)
        {close(fd);}
	for (int i = 1; i <= 5; i++)
	{
		linebuf = get_next_line(fd);
		printf("%s", linebuf);
		free(linebuf);
	}
	close(fd);
}*/
