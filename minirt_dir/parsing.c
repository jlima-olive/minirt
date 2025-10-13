/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/13 16:23:24 by namejojo         ###   ########.fr       */
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
	lst = new_lst();
	if (lst == NULL)
		close_mlx(mlx);
	lst->next = new_lst();
	if (lst->next == NULL)
		close_mlx(mlx);
	img->objs = lst;
	lst->id = 's';
	lst->obj = new_sphere(set_class(0, 0, 2), 0.5, set_class(0, 0 ,1));
	if (lst->obj == NULL)
		close_mlx(mlx); 
	lst->next->id = 's';
	lst->next->obj = new_sphere(set_class(-1, 2, 10), 2, set_class(1, 0, 0));
	img->ligh_ray = set_class(-1, -1 , 1);
}
