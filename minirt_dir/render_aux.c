/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:06:33 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:11:00 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	get_true_rgb(t_mlximg img, t_rgb color, float root)
{
	t_rgb	ref;
	t_rgb	temp;

	ref = get_negative_color(color);
	ref = sub(img.ligh_rays->color, ref);
	ref.x = (ref.x > 0) * ref.x;
	ref.y = (ref.y > 0) * ref.y;
	ref.z = (ref.z > 0) * ref.z;
	ref = mult(ref, root);
	temp = get_negative_color(color);
	temp = sub(img.a_color, temp);
	temp.x = (temp.x > 0) * temp.x;
	temp.y = (temp.y > 0) * temp.y;
	temp.z = (temp.z > 0) * temp.z;
	temp = mult(temp, img.ambient);
	ref.x = (ref.x > temp.x) * ref.x + (ref.x < temp.x) * temp.x;
	ref.y = (ref.y > temp.y) * ref.y + (ref.y < temp.y) * temp.y;
	ref.z = (ref.z > temp.z) * ref.z + (ref.z < temp.z) * temp.z;
	return (get_rgb(ref, 1));
}

int	find_ligh(t_mlximg img, t_ray ray)
{
	double	len;
	double	var1;
	double	var2;
	t_list	*lst;

	lst = img.objs;
	while (lst)
	{
		if (lst->type == SPHERE)
			len = get_sp_root(lst->obj, ray);
		else if (lst->type == PLANE)
			len = get_pl_root(ray, lst->obj);
		else if (lst->type == CYLINDER)
			len = get_cy_root(ray, lst->obj, &var1, &var2);
		if (len > 0.00000001 && len < 0.9999999)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	run_code(t_mlx *mlx)
{
	double	w;
	double	h;
	double	x;
	double	y;

	w = HGT * AP_RAT;
	h = HGT;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			render(x, y, mlx->img);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
}
