/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 20:37:14 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, WIDTH, WIDTH * 16/9, "WINDOW");
	if (mlx->mlx_ptr == NULL)
		return (1);
	return (0);
}

int	close_mlx(t_mlx *mlx)
{
	// mlx_destroy_image(data->mlx_ptr, data->img2.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int my_key_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
		close_mlx(mlx);
	return (0);
}

int my_button_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
		close_mlx(mlx);
	return (0);
}


int	main(void)
{
	t_mlx mlx;

	mlx.mlx_ptr = NULL;
	mlx.mlx_win = NULL;
	if (WIDTH != 1080)
		return (1);
	if (init_mlx(&mlx))
		return (1);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_button_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
