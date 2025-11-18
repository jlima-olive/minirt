/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:11:01 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:41:19 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_rgb	decompose_color(unsigned int color)
{
	t_rgb	ret;

	ret.x = color >> 16;
	ret.y = (color << 16) >> 24;
	ret.z = (color << 24) >> 24;
	return (ret);
}

void	get_medium_color(int x, int y, t_simpleimg img2, t_mlximg img)
{
	t_rgb	color;
	int		offset;

	offset = ((x - 1) * 4) + (y * img.line_len);
	color = decompose_color(*((unsigned int *)(img.pixel_ptr + offset)));
	offset = ((x + 1) * 4) + (y * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr
						+ offset))));
	offset = (x * 4) + ((y + 1) * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr
						+ offset))));
	offset = (x * 4) + ((y - 1) * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr
						+ offset))));
	offset = (x * 4) + (y * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr
						+ offset))));
	color = mult(color, 1.0 / 5);
	*((unsigned int *)(img2.pixel_ptr + offset)) = get_rgb(color, 1.0 / 255);
}

void	anti_aliasing(t_simpleimg img2, t_mlximg img)
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
			get_medium_color(x, y, img2, img);
	}
}
