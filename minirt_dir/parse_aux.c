/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:02:34 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/19 13:32:26 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	edge_cases_del_v(t_vec o, t_vec v)
{
	if (o.y == 0)
		return (set_class(0, -1, 0));
	if (o.x == 0 && o.z == 0)
		return (set_class(0, 0, 1));
	if (o.x == 0)
	{
		if (o.z > 0)
			return (normalize_vec(set_class(0, -o.z, o.y)));
		else
			return (normalize_vec(set_class(0, o.z, -o.y)));
	}
	if (o.z == 0)
	{
		if (o.x < 0)
			return (normalize_vec(set_class(-o.y, o.x, 0)));
		else
			return (normalize_vec(set_class(o.y, -o.x, 0)));
	}
	if (v.y > 0)
		v = mult(v, -1);
	return (normalize_vec(v));
}

t_mlximg	aux_parse(t_mlximg img)
{
	double	vp_size;

	img.wdt = HGT * AP_RAT;
	img.deg = img.fov * (img.fov <= 179.99999) + 179.99999
		* (img.fov > 179.99999);
	img.rad = ft_deg_to_rad(img.deg);
	img.ori_vec = normalize_vec(img.ori_vec);
	img.ctr_pnt = add(img.camera, img.ori_vec);
	img.del_h = set_class(img.ori_vec.z, 0, -img.ori_vec.x);
	img.del_h = add(img.del_h, mult(set_class(1, 0, 0), !vec_len(img.del_h)));
	vp_size = 2 * tan(img.rad / 2);
	img.del_h = mult(normalize_vec(img.del_h), vp_size / img.wdt);
	img.normal_h = mult(img.del_h, img.wdt);
	img.del_v = set_class(get_x(img.del_h), get_y(img.ori_vec, img.del_h), 1);
	img.del_v = mult(edge_cases_del_v(img.ori_vec, img.del_v), (vp_size
				/ AP_RAT) / HGT);
	img.pixel00 = add(img.ctr_pnt, mult(img.del_h, -img.wdt / 2));
	img.pixel00 = add(img.pixel00, mult(img.del_v, -HGT / 2));
	return (img);
}

t_objinfo	set_obj_info(void)
{
	t_objinfo	ret;

	ret.light_count = 0;
	ret.color = -1;
	ret.point = set_class(0, 0, 0);
	ret.red_vec = set_class(0, 0, 0);
	return (ret);
}

void	connect_parse(t_mlximg *img, t_scene scene)
{
	img->ambient = scene.ambient->ratio;
	img->a_color = scene.ambient->color;
	img->ori_vec = scene.camera->dir;
	img->camera = scene.camera->src;
	img->fov = scene.camera->fov;
	img->ligh_rays = scene.light;
	img->objs = scene.list;
}
