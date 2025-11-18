/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:32:51 by psantos-          #+#    #+#             */
/*   Updated: 2025/10/22 01:38:12 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static size_t	ft_linelen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

static char	*ft_findnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

static void	ft_trimbuffer(char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	j = 0;
	while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
}

static char	*ft_join_line(char *line, const char *buf)
{
	size_t	len_l;
	size_t	len_b;
	char	*new;
	size_t	i;
	size_t	j;

	len_l = ft_strlen(line);
	len_b = ft_linelen(buf);
	new = malloc(len_l + len_b + 1);
	i = 0;
	j = 0;
	if (!new)
		return (free(line), NULL);
	while (i < len_l)
	{
		new[i] = line[i];
		i++;
	}
	while (j < len_b)
		new[i++] = buf[j++];
	new[i] = '\0';
	free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = ft_strlen(buf);
	if (buf[0] == '\0')
		bytes = read(fd, buf, BUFFER_SIZE);
	while (!ft_findnl(buf) && bytes > 0)
	{
		buf[bytes] = '\0';
		line = ft_join_line(line, buf);
		ft_trimbuffer(buf);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes <= 0 && !line)
		return (NULL);
	buf[bytes] = '\0';
	line = ft_join_line(line, buf);
	ft_trimbuffer(buf);
	return (line);
}
