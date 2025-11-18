/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:24:34 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 21:44:43 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static int	parse_plane_body(char *line, t_plane *pl, t_scene *scene)
{
	int	i;

	i = 0;
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
	pl->color = mult(pl->color, 1.0 / 255);
	if (line[i] && line[i] != '\n')
	{
		if (!is_valid_int(line + i, 0, 2))
			return (write(2, "Error\npl: invalid material\n", 28), 1);
		pl->material = (t_material)parse_int(line, &i);
	}
	else
		pl->material = DEFAULT;
	pl->a = pl->normal.x;
	pl->b = pl->normal.y;
	pl->c = pl->normal.z;
	pl->d = -pl->normal.x * pl->point.x -pl->normal.y * pl->point.y -pl->normal.z * pl->point.z;
	return (0);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane	tmp;
	t_plane	*pl;
	t_list	*node;

	if (count_attributes(line) < 3 || count_attributes(line) > 4)
		return (write(2, "Error\npl: incorrect nr of attributes\n", 37), 1);
	if (parse_plane_body(line, &tmp, scene))
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
	node->obj = pl;
	node->next = scene->list;
	scene->list = node;
	scene->n_objects++;
	return (0);
}
