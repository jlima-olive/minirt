/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 22:15:42 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
precheck catches formatting errors before any allocation
allows quick and clean exit without unnecessary frees 
simplifies code later on in terms of formatting check
simplifies next parsing functions and guarantees correct formatting
(checks invalid chars, absent or wrong identifiers,
invalid scene element uniqueness and missing shape)
*/

#include "../../minirt.h"

static void	check_invalid_chars(char *line, int fd)
{
	int	i;

	if (line[0] == 0 || line[0] == '\n')
		return ;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isalpha(line[i]))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if ((!ft_isnum(line[i])) && line[i] != '.' && line[i] != ','
			&& !ft_isspace(line[i]) && !ft_issign(line[i]))
		{
			free(line);
			close(fd);
			write(2, "Error\nInvalid Character\n", 24);
			exit(1);
		}
		i++;
	}
}

static void	initial_check(int argc, char *filename)
{
	size_t	len;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./miniRT <scene.rt>\n", 33);
		exit(1);
	}
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 3, ".rt") != 0)
	{
		write(2, "Error\nInvalid file extension\n", 29);
		exit(1);
	}
}

static int	count_scene_elements(int fd, t_counts *counts)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == 'A' && ft_isspace(line[i + 1]))
			counts->count_a++;
		else if (line[i] == 'C' && ft_isspace(line[i + 1]))
			counts->count_c++;
		else if (line[i] == 'L' && ft_isspace(line[i + 1]))
			counts->count_l++;
		else if (isshape(line + i) && (ft_isspace(line[i + 2])))
			counts->count_shape++;
		else if (line[0] != '\0' && line[0] != '\n')
			return (free(line), 0);
		check_invalid_chars(line, fd);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	precheck(int argc, char *filename)
{
	int			fd;
	t_counts	counts;

	initial_check(argc, filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		return (perror("Cannot open file"), 0);
	}
	counts.count_a = 0;
	counts.count_c = 0;
	counts.count_l = 0;
	counts.count_shape = 0;
	if (!count_scene_elements(fd, &counts))
	{
		write(2, "Error\nInvalid Character\n", 24);
		return (close(fd), 0);
	}
	close(fd);
	if (counts.count_a != 1 || counts.count_c != 1
		|| counts.count_l != 1 || counts.count_shape < 1)
		return (write(2, "Error\nOnly 1 A, C, L. At least 1 shape\n", 39), 0);
	return (1);
}
