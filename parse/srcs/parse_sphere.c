/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:35:26 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/19 14:33:39 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static int	parse_sphere_body(char *line, t_sphere *sp)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!is_valid_vec(line + i))
		return (write(2, "Error\nsp: invalid center\n", 26), 1);
	parse_vec(line, &i, &sp->center);
	if (!is_valid_float(line + i, 1e-6f, FLT_MAX - 1))
		return (write(2, "Error\nsp: invalid diameter\n", 28), 1);
	sp->r = parse_float(line, &i) / 2.0f;
	if (!is_valid_rgb(line + i))
		return (write(2, "Error\nsp: invalid color\n", 25), 1);
	parse_color(line, &i, &sp->color);
	sp->color = mult(sp->color, 1.0 / 255);
	return (0);
}

int	parse_sphere(char *line, t_scene *scene)
{
	t_sphere	tmp;
	t_sphere	*sp;
	t_list		*node;

	if (count_attributes(line) < 3 || count_attributes(line) > 4)
		return (write(2, "Error\nsp: incorrect nr of attributes\n", 37), 1);
	if (parse_sphere_body(line, &tmp))
		return (1);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (perror("malloc"), 1);
	*sp = tmp;
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(sp);
		return (perror("malloc"), 1);
	}
	node->type = SPHERE;
	node->obj = sp;
	node->next = scene->list;
	scene->list = node;
	scene->n_objects++;
	return (0);
}
