/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:48:20 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:52:23 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_pl_root(t_ray ray, t_plane *pl)
{
	double	denominator;
	double	nominator;
	double	ret;

	if (dot_product(ray.dir, pl->normal) < 0.0001)
		return (-1);
	nominator = -pl->d - pl->a * ray.ori.x - pl->b * ray.ori.y - pl->c
		* ray.ori.z;
	denominator = pl->a * ray.dir.x + pl->b * ray.dir.y + pl->c * ray.dir.z;
	ret = nominator / denominator;
	if (ret != ret)
		return (-1);
	return (ret);
}

double	get_sp_root(t_sphere *sp, t_ray ray)
{
	t_vec	oc;
	double	root;
	double	a;
	double	h;
	double	c;

	oc = sub(sp->center, ray.ori);
	a = dot_product(ray.dir, ray.dir);
	h = dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - (sp->r * sp->r);
	root = h * h - a * c;
	if (root < 0)
		return (-1);
	root = sqrt(root);
	return (ft_min_pos((h + root) / a, (h - root) / a));
}

double	get_cy_root(t_ray ray, t_cylinder *cy, double *dv, double *xv)
{
	t_vec	x;
	double	a;
	double	b;
	double	c;
	double	root;

	x = new_vec(ray.ori, cy->ray.ori);
	*dv = dot_product(ray.dir, cy->ray.dir);
	*xv = dot_product(x, cy->ray.dir);
	a = dot_product(ray.dir, ray.dir) - *dv * *dv;
	if (a == 0)
		return (-1);
	b = 2 * (dot_product(ray.dir, x) - *dv * *xv);
	c = dot_product(x, x) - *xv * *xv - cy->r * cy->r;
	root = b * b - 4 * a * c;
	if (root < 0)
		return (-1);
	root = sqrt(root);
	root = root / (a * 2);
	b = -b / (a * 2);
	return (ft_min_pos(b - root, b + root));
}
