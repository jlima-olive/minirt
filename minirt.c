/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 23:14:20 by namejojo         ###   ########.fr       */
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
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HGT * 16 / 9, HGT, "minirt");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * 16/9, HGT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr
	= mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
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

int	get_color(float y)
{
	y = (y / HGT);
	return (get_rgb_num(0.5, 0.3, 0, y) + get_rgb_num(0.5, 0.7, 1, 1));
}

void	render_background(int x, int y, t_mlximg img)
{
	int	offset;
	
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(y);
}

void	paint_back_ground(t_mlx *mlx)
{
	int	w;
	int	x;
	int	y;

	w = HGT * 16 / 9;
	y = -1;
	while (++y < HGT)
	{
		x = -1;
		while (++x < w)
			render_background(x, y, mlx->img);
	}
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
}

void	my_pixel_put(int x, int y, t_mlximg img)
{
	int	offset;
	
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(y);
}

void	run_code(t_mlx *mlx)
{
	int	w;
	int	x;
	int	y;

	w = HGT * 16 / 9;
	y = -1;
	while (++y < HGT)
	{
		x = -1;
		while (++x < w)
			my_pixel_put(x, y, mlx->img);
	}
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
}

int	vec_len(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_mlximg parse(t_mlximg img)
{
	int		wdt;
	int		rad;
	int		degree;

	wdt = HGT * 16 / 9;
	degree = 90;
	rad = degree / 180;
	img.camera = set_class(0, 0, 0);
	img.ori_vec = set_class(0, 0, 1);
	img.ori_vec = mult_class(img.ori_vec, 1 / vec_len(img.ori_vec));
	img.ctr_pnt = add(img.camera, img.ctr_pnt);
	// probably all wrong under here
	img.pixel00 = add(img.ctr_pnt, set_class(-rad, 1, 1));
	img.del_x = set_class(rad / HGT, 0, 0);
	img.del_y = set_class(0, -2 , 0);
	return (img);
}

int	main(void)
{
	t_mlx	mlx;
	t_point	camera_center;
	t_point	pixel;

	if (HGT != 720)
		return (1);
	init_var(&mlx);
	if (init_mlx(&mlx))
		return (1);
	mlx.img = parse(mlx.img);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, ButtonPress, ButtonPressMask, my_button_hook, &mlx);
	paint_back_ground(&mlx);
	run_code(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
