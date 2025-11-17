/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:40:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/17 17:37:25 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_sphere *new_sphere(t_point center, double r, t_rgb color)
{
	t_sphere *obj;

	obj = malloc(sizeof(t_sphere));
	obj->center = center;
	obj->r = r;
	obj->color = color;
	return (obj);
}

t_plane *new_plane(t_mlximg *img, t_point normal, t_point pt, t_rgb color)
{
	t_plane *obj;

	normal = normalize_vec(normal);
	obj = malloc(sizeof(t_plane));
	obj->color = color;
	if (dot_product(normal, new_vec(pt, img->camera)) <= 0)
		normal = mult(normal, -1);
	obj->normal = normal;
	obj->point = pt;
	obj->a = normal.x;
	obj->b = normal.y;
	obj->c = normal.z;
	obj->d = -normal.x * pt.x -normal.y * pt.y -normal.z * pt.z;
	return (obj);
}

t_list	*new_lst(void)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	ret->next = NULL;
	return (ret);
}

void	add_obj(t_mlximg *img, void *obj, char type)
{
	t_list	*walk;
	
	if (img->objs == NULL)
	{
		img->objs = new_lst();
		if (img->objs)
		{
			img->objs->type = type;
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
		walk->next->type = type;
		walk->next->obj = obj;
	}
}

void	print_obj(t_mlximg *img)
{
	t_list *walk = img->objs;

	printf("here\n");
	while (walk)
	{
		if (walk->type == SPHERE)
		{
			printf("type = %c --center(%f, %f, %f)\n", walk->type,
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

t_cylinder	*new_cylinder(t_point base, t_vec normal, t_rgb color, double r)
{
	t_cylinder *obj;

	obj = malloc(sizeof(t_cylinder));
	obj->ray.ori = base;
	obj->ray.dir = normal;
	obj->r = r;
	obj->color = color;
	return (obj);
}

void get_objs(t_mlx *mlx)
{
	t_mlximg	*img;

	img = &mlx->img;
	// img->ligh_ray = set_class(0, 10, 0);
	img->objs = NULL;
	img->ligh_rays = NULL;
	img->total_lights = 0;
	add_light(img, set_class(-2, 6, 3), set_class(1, 1, 1));

	// add_light(img, set_class(-1, 0, 2), set_class(1, 1, 1));
	// print_light(img);

	add_obj(img, new_sphere(set_class(0, 1, 2), 0.5, set_class(0, 0 ,1)), SPHERE);

	add_obj(img, new_sphere(set_class(-6, 6, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(-6, -6, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(6, 6, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(6, -6, 2), 2, set_class(1, 0, 0)), SPHERE);

	add_obj(img, new_sphere(set_class(-6, 0, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(6, 0, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(0, 6, 2), 2, set_class(1, 0, 0)), SPHERE);
	add_obj(img, new_sphere(set_class(0, -6, 2), 2, set_class(1, 0, 0)), SPHERE);

	// add_obj(img, new_cylinder(set_class(-6, 0, -2), set_class(0, 0, 2), set_class(1, 1, 1), 0.1), CYLINDER);
	add_obj(img, new_cylinder(set_class(-10, 0, 15), set_class(0, 1, 0), set_class(1, 0, 0), 2), CYLINDER);
	add_obj(img, new_cylinder(set_class(10, 0, 15), set_class(0, 1, 0), set_class(0, 1, 0), 2), CYLINDER);
	
	add_obj(img, new_plane(img, set_class(0, 1, 0), set_class(0, -10, 0), set_class(1, 0, 0)), PLANE);
	add_obj(img, new_plane(img, set_class(1, 0, 0), set_class(-15, 0, 0), set_class(1, 1, 0)), PLANE);
	add_obj(img, new_plane(img, set_class(1, 0, 0), set_class(20, 0, 0), set_class(1, 1, 0)), PLANE);
	// add_obj(img, new_plane(img, set_class(0, 0, 1), set_class(0, 0, 20), set_class(0, 1, 1)), PLANE);
	add_obj(img, new_plane(img, set_class(0, 1, 0), set_class(0, 20, 0), set_class(0, 1, 1)), PLANE);
	print_obj(img);
	img->ambient = 0.1;
	// exit(0);
}
