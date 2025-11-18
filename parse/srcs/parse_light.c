/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:50:27 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 23:13:09 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_light_attributes(char *line, t_vec *src,
								float *brightness, t_rgb *color)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_vec(line + i))
		return (write(2, "Error\nL: invalid position\n", 27), 1);
	parse_vec(line, &i, src);
	if (!is_valid_float(line + i, 0.0f, 1.0f))
		return (write(2, "Error\nL: invalid brightness ratio\n", 34), 1);
	*brightness = parse_float(line, &i);
	if (!is_valid_rgb(line + i))
		return (write(2, "Error\nL: invalid color\n", 24), 1);
	parse_color(line, &i, color);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	t_vec	src;
	float	brightness;
	t_rgb	color;

	if (count_attributes(line) != 3)
		return (write(2, "Error\nL: incorrect nr of attributes\n", 36), 1);
	if (parse_light_attributes(line, &src, &brightness, &color) == 1)
		return (1);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		return (perror("malloc"), 1);
	scene->light->src = src;
	scene->light->brightness = brightness;
	scene->light->color = mult(color, 1.0 / 255);
	scene->light->next = NULL;
	return (0);
}
