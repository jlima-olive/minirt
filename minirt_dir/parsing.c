/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/15 20:45:25 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_sphere *new_sphere(t_point center, float radius, t_rgb color)
{
	t_sphere *obj;

	obj = malloc(sizeof(t_sphere));
	obj->center = center;
	obj->radius = radius;
	obj->color = color;
	return (obj);
}

t_lst	*new_lst(void)
{
	t_lst	*ret;

	ret = malloc(sizeof(t_lst));
	ret->next = NULL;
	return (ret);
}

void get_objs(t_mlx *mlx)
{
	t_lst		*lst;
	t_mlximg	*img;

	img = &mlx->img;
	img->ligh_ray = set_class(1, -1, 1);
	lst = new_lst();
	if (lst == NULL)
		close_mlx(mlx);
	img->objs = lst;
	lst->id = 's';
	lst->obj = new_sphere(set_class(0, 0, 2), 0.5, set_class(0, 0 ,1));
	if (lst->obj == NULL)
		close_mlx(mlx); 
	lst->next = new_lst();
	if (lst->next == NULL)
		close_mlx(mlx);
	lst->next->id = 's';
	lst->next->obj = new_sphere(set_class(-6, 0, 3), 2, set_class(1, 0, 0));
	lst->next->next = new_lst();
	if (lst->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->id = 's';
	lst->next->next->obj = new_sphere(set_class(6, 0, 3), 2, set_class(1, 0, 0));


	lst->next->next->next = new_lst();
	if (lst->next->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->next->id = 's';
	lst->next->next->next->obj = new_sphere(set_class(0, 6, 3), 2, set_class(1, 0, 0));

	lst->next->next->next->next = new_lst();
	if (lst->next->next->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->next->next->id = 's';
	lst->next->next->next->next->obj = new_sphere(set_class(0, -6, 3), 2, set_class(1, 0, 0));
}
