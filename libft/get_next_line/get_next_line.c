/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:50:26 by gregueir          #+#    #+#             */
/*   Updated: 2025/08/06 12:47:34 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gnl_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

static char	*update_backup(char *backup)
{
	int		i;
	int		newline;
	char	*temp;

	newline = 0;
	i = 0;
	temp = NULL;
	while (backup && backup[i] && !newline)
	{
		if (backup[i] == '\n')
			newline++;
		i++;
	}
	if (newline)
	{
		temp = ft_gnl_strdup(backup + i, 0);
		if (!temp)
			return (ft_gnl_free(backup));
		ft_gnl_free(backup);
		return (temp);
	}
	ft_gnl_free(backup);
	return (temp);
}

static char	*clean_line(char *line)
{
	int		len;
	char	*buffer;

	if (!line)
		return (NULL);
	len = 0;
	buffer = ft_gnl_strdup(line, 0);
	if (ft_gnl_strchr(buffer, '\n'))
	{
		while (buffer && buffer[len] != '\n')
			len++;
		len++;
		buffer[len] = '\0';
		ft_gnl_free(line);
		return (buffer);
	}
	else
	{
		free(buffer);
		return (line);
	}
}

static char	*read_file(char *backup, int fd)
{
	ssize_t		rd;
	char		*buffer;

	if (!backup)
	{
		backup = ft_gnl_strdup("", 1);
		if (!backup)
			return (NULL);
	}
	rd = BUFFER_SIZE + 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	while (rd > 0 && !ft_gnl_strchr(buffer, '\n') && rd >= BUFFER_SIZE)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (ft_gnl_free(buffer), ft_gnl_free(backup));
		buffer[rd] = '\0';
		backup = ft_gnl_strjoin(backup, buffer);
	}
	ft_gnl_free(buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*backup = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	backup = read_file(backup, fd);
	if (!backup)
		return (NULL);
	tmp = ft_gnl_strdup(backup, 0);
	line = clean_line(tmp);
	backup = update_backup(backup);
	if (backup && !*backup)
	{
		ft_gnl_free(backup);
		return (line);
	}
	return (line);
}
