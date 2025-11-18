/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:38:03 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 15:50:10 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

double	square_vec(t_vec vec)
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
