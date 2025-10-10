/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 13:42:21 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int	init_mlx(t_mlx *mlx)
{
	t_mlximg	img;

	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		close_mlx(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HEIGHT * 16/9, HEIGHT, "WINDOW");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HEIGHT * 16/9, HEIGHT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	mlx->img = img;
	if (img.pixel_ptr == NULL)
		close_mlx(mlx);
	return (0);
}

void	init_var(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

int	get_color(int x, int y, t_mlximg img)
{
	
}

void	my_pixel_put(int x, int y, t_mlximg img)
{
	int	offset;
	
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(x, y, img);
}

void	paint_back_ground(t_mlx *mlx)
{
	int	w;
	int	x;
	int	y;

	w = HEIGHT * 16 / 9;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < w)
			my_pixel_put(x, y, mlx->img);
	}
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
}

t_mlximg parse(t_mlximg img)
{
	t_vec	focus_point;

	img.camera = set_class(0, 0, 0);
	focus_point = set_class(0, 0, 1);
	focus_point = mult_class(focus_point, 1 / normalize_vec(focus_point));
	img.focus_point = focus_point;
	return (img);
}

int	main(void)
{
	t_mlx	mlx;
	t_point	camera_center;
	t_point	pixel;

	if (HEIGHT != 540)
		return (1);
	init_var(&mlx);
	if (init_mlx(&mlx))
		return (1);
	mlx.img = parse(mlx.img);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, ButtonPress, ButtonPressMask, my_button_hook, &mlx);
	paint_back_ground(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
