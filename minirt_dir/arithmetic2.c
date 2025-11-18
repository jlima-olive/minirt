/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:38:28 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 15:49:35 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_x(t_vec h)
{
	return (-h.z / h.x);
}

double	get_y(t_vec o, t_vec h)
{
	return ((h.z * o.x - o.z * h.x) / (o.y * h.x));
	return ((((-h.z * o.x) / h.x) + o.z) / -o.y);
}

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	div_product(t_vec a, t_vec b)
{
	return (a.x / b.x + a.y / b.y + a.z / b.z);
}

t_point	point_at(t_ray ray, double t)
{
	return (add(ray.ori, mult(ray.dir, t)));
}
