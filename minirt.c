/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 09:56:04 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int	init_mlx(t_mlx *mlx)
{
	t_mlximg	*img;

	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		close_mlx(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, WIDTH * 16/9, "WINDOW");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img = mlx_new_image(mlx->mlx_ptr, WIDTH, WIDTH * 16/9);
	if (img == NULL)
		close_mlx(mlx);
	mlx->img = img;
	img->pixel_ptr
	= mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	if (img->pixel_ptr == NULL)
		close_mlx(mlx);
	return (0);
}

void	init_var(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
}

void	my_pixel_put(int x, int y, t_mlx *mlx)
{
	int	offset;
	
	offset = (x * (mlx->img->bpp / 8)) + (y * mlx->img->line_len);
	*((unsigned int *)(mlx->img->pixel_ptr + offset)) = 255;
}

void	paint_back_ground(t_mlx *mlx)
{
	int	h;
	int	x;
	int	y;

	h = WIDTH * 16 / 9;
	y = -1;
	printf("doing something1\n");
	fflush(stdout);
	while (++y < h)
	{
		x = -1;
		while (++x < WIDTH)
			my_pixel_put(x, y, mlx);
	}
	printf("doing something2\n");
	fflush(stdout);
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img->img_ptr, WIDTH, h);
}

int	main(void)
{
	t_mlx mlx;

	init_var(&mlx);
	if (WIDTH != 1080)
		return (1);
	if (init_mlx(&mlx))
		return (1);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, ButtonPress, ButtonPressMask, my_button_hook, &mlx);
	paint_back_ground(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
