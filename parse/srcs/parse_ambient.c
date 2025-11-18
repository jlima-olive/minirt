/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:57:31 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/18 11:13:03 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	parse_ambient(char *line, t_scene *scene)
{
	int		i;
	float	ratio;
	t_rgb	color;

	i = 0;
	if (count_attributes(line) != 2)
		return (write(2, "Error\nA: incorrect nr of attributes\n", 36), 1);
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_float(line + i, 0.0f, 1.0f))
		return (write(2, "Error\nA: invalid ratio\n", 23), 1);
	ratio = parse_float(line, &i);
	if (!is_valid_rgb(line + i))
		return (write(2, "Error\nA: invalid color\n", 23), 1);
	parse_color(line, &i, &color);
	scene->ambient = malloc(sizeof(t_ambient));
	if (!scene->ambient)
		return (perror("malloc"), 1);
	scene->ambient->ratio = ratio;
	return (0);
}
