/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:42:02 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:57:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_objinfo	hit_cylinder(t_mlximg img, t_cylinder *cy, t_ray ray,
		t_light *light)
{
	t_objinfo	info;
	t_point		temp;
	double		root;
	double		dv;
	double		xv;

	root = get_cy_root(ray, cy, &dv, &xv);
	info = set_obj_info();
	if (root < 0)
		return (info);
	info.point = point_at(ray, root);
	temp = point_at(cy->ray, dv * root + xv);
	temp = new_vec(info.point, temp);
	ray.dir = new_vec(light->src, info.point);
	root = get_cos(ray.dir, temp);
	if (root < 0)
		root = 0;
	ray = set_ray(info.point, mult(ray.dir, 1));
	if (find_ligh(img, ray))
		root = 0;
	info.color = get_true_rgb(img, cy->color, root * img.ligh_rays->brightness);
	return (info);
}

t_objinfo	hit_plane(t_mlximg img, t_plane *pl, t_ray ray, t_light *light)
{
	t_vec		pl_light;
	t_objinfo	info;
	double		root;

	root = get_pl_root(ray, pl);
	info = set_obj_info();
	if (root < 0 || root > 100000)
		return (info);
	info.point = point_at(ray, root);
	pl_light = new_vec(info.point, light->src);
	root = get_cos(pl->normal, pl_light);
	if (root < 0)
		root = 0;
	ray = set_ray(info.point, mult(pl_light, -1));
	if (find_ligh(img, ray))
		root = 0;
	info.color = get_true_rgb(img, pl->color, root * img.ligh_rays->brightness);
	return (info);
}

t_objinfo	hit_sphere(t_mlximg img, t_sphere *sp, t_ray ray, t_light *light)
{
	t_objinfo	info;
	t_vec		pl;
	t_vec		cp;
	double		root;

	root = get_sp_root(sp, ray);
	info = set_obj_info();
	if (root < 0)
		return (info);
	info.point = point_at(ray, root);
	cp = mult(new_vec(info.point, sp->center), -1 / sp->r);
	pl = new_vec(info.point, light->src);
	root = get_cos(cp, pl);
	if (root < 0)
		root = 0;
	ray = set_ray(info.point, mult(pl, -1));
	if (find_ligh(img, ray))
		root = 0;
	info.color = get_true_rgb(img, sp->color, root * img.ligh_rays->brightness);
	return (info);
}

int	get_color(t_mlximg img, double y, t_ray ray)
{
	t_objinfo	value;
	t_objinfo	new_v;
	t_list		*lst;
	double		len;

	lst = img.objs;
	value = set_obj_info();
	while (lst)
	{
		if (lst->type == SPHERE)
			new_v = hit_sphere(img, lst->obj, ray, img.ligh_rays);
		else if (lst->type == PLANE)
			new_v = hit_plane(img, lst->obj, ray, img.ligh_rays);
		else if (lst->type == CYLINDER)
			new_v = hit_cylinder(img, lst->obj, ray, img.ligh_rays);
		len = vec_len(new_vec(img.camera, new_v.point));
		if (value.color == -1 || (new_v.color != -1
				&& len < vec_len(new_vec(img.camera, value.point))))
			value = new_v;
		lst = lst->next;
	}
	if (value.color != -1)
		return (value.color);
	y = y / HGT;
	return (get_rgb_num(0.5, 0.3, 0, y) + get_rgb_num(0.5, 0.7, 1, 1));
}

void	render(int x, int y, t_mlximg img)
{
	int		offset;
	t_ray	ray;

	ray = get_ray(img, (int)(x), (int)(y));
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset)) = get_color(img, (int)(y), ray);
}
