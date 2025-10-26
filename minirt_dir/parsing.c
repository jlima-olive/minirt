/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/26 18:48:13 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_sphere *new_sphere(t_point center, double radius, t_rgb color)
{
	t_sphere *obj;

	obj = malloc(sizeof(t_sphere));
	obj->center = center;
	obj->radius = radius;
	obj->color = color;
	return (obj);
}

t_plane *new_plane(t_mlximg *img, t_point norm, t_point pt, t_rgb color)
{
	t_plane *obj;

	norm = normalize_vec(norm);
	obj = malloc(sizeof(t_plane));
	obj->color = color;
	if (dot_product(norm, new_vec(pt, img->camera)) <= 0)
		norm = mult(norm, -1);
	obj->norm = norm;
	obj->point = pt;
	obj->a = norm.x;
	obj->b = norm.y;
	obj->c = norm.z;
	obj->d = -norm.x * pt.x -norm.y * pt.y -norm.z * pt.z;
	return (obj);
}

t_lst	*new_lst(void)
{
	t_lst	*ret;

	ret = malloc(sizeof(t_lst));
	ret->next = NULL;
	return (ret);
}

void	add_obj(t_mlximg *img, void *obj, char id)
{
	t_lst	*walk;
	
	if (img->objs == NULL)
	{
		img->objs = new_lst();
		if (img->objs)
		{
			img->objs->id = id;
			img->objs->obj = obj;
		}
		return ;
	}
	walk = img->objs;
	while (walk->next)
		walk = walk->next;
	walk->next = new_lst();
	if (walk->next)
	{
		walk->next->id = id;
		walk->next->obj = obj;
	}
}

void	print_obj(t_mlximg *img)
{
	t_lst *walk = img->objs;

	printf("here\n");
	while (walk)
	{
		if (walk->id == 's')
		{
			printf("id = %c --center(%f, %f, %f)\n", walk->id,
			((t_sphere *)walk->obj)->center.x,
			((t_sphere *)walk->obj)->center.y,
			((t_sphere *)walk->obj)->center.z);
		}
		walk = walk->next;
	}
}

t_light	*new_light()
{
	t_light	*ret;

	ret = malloc(sizeof(t_light));
	if (ret)
		ret->next = NULL;
	return (ret);
}

void	add_light(t_mlximg *img, t_point src, t_rgb color)
{
	t_light	*walk;
	
	if (img->ligh_rays == NULL)
	{
		img->ligh_rays = new_light();
		if (img->ligh_rays)
		{
			img->ligh_rays->color =color;
			img->ligh_rays->src = src;
		}
		img->total_lights++;
		return ;
	}
	walk = img->ligh_rays;
	while (walk->next)
		walk = walk->next;
	walk->next = new_light();
	if (walk->next)
	{
		walk->next->color = color;
		walk->next->src = src;
	}
	img->total_lights++;
}

void	print_light(t_mlximg *img)
{
	t_light	*light;

	light = img->ligh_rays;
	while (light)
	{
		printf("%f %f %f\n", light->color.x, light->color.y, light->color.z);
		light = light->next;
	}
}

t_cylidner	*new_cylinder(t_point base, t_vec norm, t_rgb color, double r)
{
	t_cylidner *obj;

	obj = malloc(sizeof(t_cylidner));
	obj->ray.ori = base;
	obj->ray.dir = norm;
	obj->r = r;
	obj->color = color;
	return (obj);
}

void get_objs(t_mlx *mlx)
{
	t_lst		*lst;
	t_mlximg	*img;

	img = &mlx->img;
	// img->ligh_ray = set_class(0, 10, 0);
	img->objs = NULL;
	img->ligh_rays = NULL;
	img->total_lights = 0;
	add_light(img, set_class(-10, 0, 2), set_class(1, 1, 1));
	// add_light(img, set_class(-1, 0, 2), set_class(1, 1, 1));
	// print_light(img);
	add_obj(img, new_sphere(set_class(0, 0, 2), 0.5, set_class(0, 0 ,1)), 's');

	add_obj(img, new_sphere(set_class(-6, 6, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(-6, -6, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(6, 6, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(6, -6, 2), 2, set_class(1, 0, 0)), 's');

	add_obj(img, new_sphere(set_class(-6, 0, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(6, 0, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(0, 6, 2), 2, set_class(1, 0, 0)), 's');
	add_obj(img, new_sphere(set_class(0, -6, 2), 2, set_class(1, 0, 0)), 's');

	// add_obj(img, new_cylinder(set_class(-6, 0, -2), set_class(0, 0, 2), set_class(1, 1, 1), 0.1), 'c');
	add_obj(img, new_cylinder(set_class(-10, 0, 15), set_class(0, 1, 0), set_class(1, 1, 1), 2), 'c');
	add_obj(img, new_cylinder(set_class(10, 0, 15), set_class(0, 1, 0), set_class(1, 1, 1), 2), 'c');
	
	
	add_obj(img, new_plane(img, set_class(0, 1, 0), set_class(0, -20, 0), set_class(1, 0, 0)), 'p');
	add_obj(img, new_plane(img, set_class(1, 0, 0), set_class(-20, 0, 0), set_class(1, 2, 0)), 'p');
	add_obj(img, new_plane(img, set_class(1, 0, 0), set_class(20, 0, 0), set_class(1, 0, 1)), 'p');
	add_obj(img, new_plane(img, set_class(0, 0, 1), set_class(0, 0, 20), set_class(0, 1, 1)), 'p');
	add_obj(img, new_plane(img, set_class(0, 1, 0), set_class(0, 20, 0), set_class(0, 0, 1)), 'p');
	print_obj(img);
}

/* void get_objs(t_mlx *mlx)
{
	t_lst		*lst;
	t_mlximg	*img;

	img = &mlx->img;
	img->ligh_ray = set_class(1, -1, 1);

	lst = new_lst();
	img->objs = lst;
	if (lst == NULL)
		close_mlx(mlx);
	lst->id = 's';
	lst->obj = new_sphere(set_class(0, 0, 2), 0.5, set_class(0, 0 ,1));

	lst->next = new_lst();
	if (lst->next == NULL)
		close_mlx(mlx);
	lst->next->id = 's';
	lst->next->obj = new_sphere(set_class(-6, 0, 2), 2, set_class(1, 0, 0));

	lst->next->next = new_lst();
	if (lst->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->id = 's';
	lst->next->next->obj = new_sphere(set_class(6, 0, 2), 2, set_class(1, 0, 0));

	lst->next->next->next = new_lst();
	if (lst->next->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->next->id = 's';
	lst->next->next->next->obj = new_sphere(set_class(0, 6, 2), 2, set_class(1, 0, 0));

	lst->next->next->next->next = new_lst();
	if (lst->next->next->next->next == NULL)
		close_mlx(mlx);
	lst->next->next->next->next->id = 's';
	lst->next->next->next->next->obj = new_sphere(set_class(0, -6, 2), 2, set_class(1, 0, 0));
	print_obj(img);
} */
