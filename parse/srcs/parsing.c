/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:07:08 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/19 14:26:50 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_line(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'A')
		return (parse_ambient(line + i + 1, scene));
	else if (line[i] == 'C')
		return (parse_camera(line + i + 1, scene));
	else if (line[i] == 'L')
		return (parse_light(line + i + 1, scene));
	else if (ft_strncmp(line + i, "sp", 2) == 0)
		return (parse_sphere(line + i + 2, scene));
	else if (ft_strncmp(line + i, "pl", 2) == 0)
		return (parse_plane(line + i + 2, scene));
	else if (ft_strncmp(line + i, "cy", 2) == 0)
		return (parse_cylinder(line + i + 2, scene));
	else
		return (0);
}

void	parse(char *filename, t_scene *scene)
{
	int		fd;
	int		result;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCannot open file");
		exit(1);
	}
	result = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			result = parse_line(line, scene);
		free(line);
		if (result)
		{
			clean_scene(scene);
			return (close(fd), exit(1));
		}
		line = get_next_line(fd);
	}
	close(fd);
}
