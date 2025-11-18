/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   artithmetic3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:04:31 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:05:06 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	get_cos(t_vec a, t_vec b)
{
	double	len;

	len = (vec_len(a) * vec_len(b));
	return (dot_product(a, b) / len);
}

t_rgb	get_negative_color(t_rgb color)
{
	return (set_class(1 - color.x, 1 - color.y, 1 - color.z));
}
