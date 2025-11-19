/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:04:22 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/19 14:33:02 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_cylinder_body(char *line, t_cylinder *cy, int i)
{
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_vec(line + i))
		return (write(2, "Error\ncy: invalid center\n", 25), 1);
	parse_vec(line, &i, &cy->center);
	if (!is_valid_vec(line + i))
		return (write(2, "Error\ncy: invalid axis\n", 23), 1);
	parse_vec(line, &i, &cy->axis);
	if (ft_is_zerovec(&cy->axis))
		return (write(2, "Error\ncy: invalid axis\n", 23), 1);
	cy->axis = normalize_vec(cy->axis);
	if (!is_valid_float(line + i, 1e-6f, FLT_MAX - 1))
		return (write(2, "Error\ncy: invalid diameter\n", 27), 1);
	cy->r = parse_float(line, &i) / 2.0f;
	if (!is_valid_float(line + i, 1e-6f, FLT_MAX))
		return (write(2, "Error\ncy: invalid height\n", 25), 1);
	cy->height = parse_float(line, &i);
	if (!is_valid_rgb(line + i))
		return (write(2, "Error\ncy: invalid color\n", 24), 1);
	parse_color(line, &i, &cy->color);
	cy->color = mult(cy->color, 1.0 / 255);
	cy->ray = set_ray(cy->center, cy->axis);
	return (0);
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	tmp;
	t_cylinder	*cy;
	t_list		*node;

	if (count_attributes(line) < 5 || count_attributes(line) > 6)
		return (write(2, "Error\ncy: incorrect nr of attributes\n", 38), 1);
	if (parse_cylinder_body(line, &tmp, 0))
		return (1);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		return (perror("malloc"), 1);
	*cy = tmp;
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(cy);
		return (perror("malloc"), 1);
	}
	node->type = CYLINDER;
	node->obj = cy;
	node->next = scene->list;
	scene->list = node;
	scene->n_objects++;
	return (0);
}
