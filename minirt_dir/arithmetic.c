/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:35:51 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/26 18:43:14 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_point	add(t_point one, t_point two)
{
	t_point ret;

	ret.x = one.x + two.x;
	ret.y = one.y + two.y;
	ret.z = one.z + two.z;
	return (ret);
}

t_point	sub(t_point one, t_point two)
{
	t_point ret;

	ret.x = one.x - two.x;
	ret.y = one.y - two.y;
	ret.z = one.z - two.z;
	return (ret);
}

t_point	mult(t_point point, double a)
{
	t_point	ret;

	ret.x = point.x * a;
	ret.y = point.y * a;
	ret.z = point.z * a;
	return (ret);
}

int	equal(t_point one, t_point two)
{
	return ((one.x == two.x) && (one.y == two.y) && (one.z == two.z));
}

int	get_rgb_num(double r, double g, double b, double a)
{
	r = r * 255 * a;
	g = g * 255 * a;
	b = b * 255 * a;
	return (((int)(r * a) << 16) + ((int)(g * a) << 8) + (int)(b * a));
}

int	get_rgb(t_point one, double a)
{
	int	r;
	int	g;
	int	b;

	r = one.x * 255 * a;
	g = one.y * 255 * a;
	b = one.z * 255 * a;
	return ((r << 16) + (g << 8) + b);
}

float	square_vec(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec_len(t_vec vec)
{
	return (sqrt(square_vec(vec)));
}

t_vec	normalize_vec(t_vec vec)
{
	return (mult(vec, 1 / vec_len(vec)));
}

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
