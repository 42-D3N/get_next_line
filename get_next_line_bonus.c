/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-pape <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:10:40 by tle-pape          #+#    #+#             */
/*   Updated: 2024/11/23 09:14:47 by tle-pape         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_bzero(void *s, size_t n)
{
	int				i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *) s;
	while (n > 0)
	{
		str[i] = '\0';
		i++;
		n--;
	}
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;

	if (nmemb * size > 2147483647)
		return (NULL);
	mem = (unsigned char *) malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

static char	*get_end_line(char *buffer)
{
	char	*res;
	int		i;
	int		j;

	if (!buffer || !*buffer)
		return (NULL);
	res = NULL;
	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	res = ft_substr(buffer, 0, i + 1);
	if (!res)
		return (NULL);
	if (buffer[i] == '\n')
		i++;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
	return (res);
}

static char	*get_the_line(char *buffer, int fd)
{
	char	*tmp;
	char	*reader;
	ssize_t	bytes;

	reader = malloc((sizeof(char *) * BUFFER_SIZE + 1));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, reader, BUFFER_SIZE);
		if (bytes < 0)
			return (free(reader), free(buffer), NULL);
		reader[bytes] = '\0';
		tmp = ft_strjoin(buffer, reader);
		if (!tmp)
			return (free(reader), free(buffer), NULL);
		free(buffer);
		buffer = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(reader);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = (char *)ft_calloc(1, sizeof(char));
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = get_the_line(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = get_end_line(buffer[fd]);
	if (!line || *line == '\0')
		return (free(buffer[fd]), free(line), buffer[fd] = NULL, NULL);
	if (*buffer[fd] == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
/*
int	main(void)
{
	int		fd;
	int		fd2;
	char	*next_line_fd1;
	char	*next_line_fd2;
	int		count;

	count = 0;
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	fd2 = open("text.txt", O_RDONLY);
	if (fd2 < 0)
		return (1);
	next_line_fd1 = get_next_line(fd);
	next_line_fd2 = get_next_line(fd2);
	while (next_line_fd1 || next_line_fd2)
	{
		if (next_line_fd1)
		{
			count++;
			printf("[%d] (fd1): %s", count, next_line_fd1);
			free(next_line_fd1);
			next_line_fd1 = get_next_line(fd);
		}
		if (next_line_fd2)
		{
			count++;
			printf("[%d] (fd2): %s", count, next_line_fd2);
			free(next_line_fd2);
			next_line_fd2 = get_next_line(fd2);
		}
	}
	close(fd);
	close(fd2);
	return (0);
}*/
