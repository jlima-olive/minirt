/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:24:34 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/19 14:31:11 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_plane_body_aux(t_plane *pl)
{
	pl->a = pl->normal.x;
	pl->b = pl->normal.y;
	pl->c = pl->normal.z;
	pl->d = -pl->normal.x * pl->point.x - pl->normal.y * pl->point.y
		- pl->normal.z * pl->point.z;
	return (0);
}

static int	parse_plane_body(char *line, t_plane *pl, t_scene *scene, int i)
{
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_vec(line + i))
		return (write(2, "Error\npl: invalid point\n", 25), 1);
	parse_vec(line, &i, &pl->point);
	if (!is_valid_vec(line + i))
		return (write(2, "Error\npl: invalid normal\n", 26), 1);
	parse_vec(line, &i, &pl->normal);
	if (ft_is_zerovec(&pl->normal))
		return (write(2, "Error\npl: invalid normal\n", 26), 1);
	pl->normal = normalize_vec(pl->normal);
	if (dot_product(pl->normal, new_vec(pl->point, scene->camera->src)) <= 0)
		pl->normal = mult(pl->normal, -1);
	if (!is_valid_rgb(line + i))
		return (write(2, "Error\npl: invalid color\n", 25), 1);
	parse_color(line, &i, &pl->color);
	return (parse_plane_body_aux(pl));
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	tmp;
	t_plane	*pl;
	t_list	*node;

	if (count_attributes(line) < 3 || count_attributes(line) > 4)
		return (write(2, "Error\npl: incorrect nr of attributes\n", 37), 1);
	if (parse_plane_body(line, &tmp, scene, 0))
		return (1);
	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (perror("malloc"), 1);
	*pl = tmp;
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(pl);
		return (perror("malloc"), 1);
	}
	node->type = PLANE;
	pl->color = mult(pl->color, 1.0 / 255);
	node->obj = pl;
	node->next = scene->list;
	scene->list = node;
	scene->n_objects++;
	return (0);
}
