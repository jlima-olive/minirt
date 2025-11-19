/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:35:51 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/19 13:32:35 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	get_ray(t_mlximg img, double x, double y)
{
	t_ray	ray;
	t_vec	vp_position;

	if (x == 0 && img.fov == 180)
		return (set_ray(img.camera, sub(img.camera, mult(img.del_h, -1))));
	if (x == img.wdt && img.fov == 180)
		return (set_ray(img.camera, sub(img.camera, mult(img.del_h, 1))));
	ray.ori = img.camera;
	vp_position = add(img.pixel00, mult(img.del_h, x));
	vp_position = add(vp_position, mult(img.del_v, y));
	ray.dir = normalize_vec(new_vec(vp_position, ray.ori));
	return (ray);
}

t_point	set_class(double x, double y, double z)
{
	t_point	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_ray	set_ray(t_point origin, t_vec direction)
{
	t_ray	ret;

	ret.ori = origin;
	ret.dir = direction;
	ret.t = 0;
	return (ret);
}

t_vec	new_vec(t_point a, t_point b)
{
	return (sub(a, b));
}
