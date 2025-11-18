/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:07:02 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_camera_attributes(char *line, t_vec *src,
									t_vec *dir, float *fov)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_vec(line + i))
		return (write(2, "Error\nC: invalid viewpoint\n", 27), 1);
	parse_vec(line, &i, src);
	if (!is_valid_vec(line + i))
		return (write(2, "Error\nC: invalid orientation\n", 29), 1);
	parse_vec(line, &i, dir);
	if (ft_is_zerovec(dir))
		return (write(2, "Error\nC: invalid orientation\n", 29), 1);
	if (!is_valid_float(line + i, 0.0f, 180.0f))
		return (write(2, "Error\nC: invalid FOV\n", 22), 1);
	*fov = parse_float(line, &i);
	return (0);
}

int	parse_camera(char *line, t_scene *scene)
{
	t_vec	src;
	t_vec	dir;
	float	fov;

	if (count_attributes(line) != 3)
		return (write(2, "Error\nC: incorrect nr of attributes\n", 36), 1);
	if (parse_camera_attributes(line, &src, &dir, &fov) == 1)
		return (1);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (perror("malloc"), 1);
	scene->camera->src = src;
	scene->camera->dir = dir;
	scene->camera->fov = fov;
	return (0);
}
