/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 16:20:36 by namejojo         ###   ########.fr       */
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

void	close_mlx(t_mlx mlx)
{
	mlx_destroy_window(mlx.mlx_ptr, mlx.mlx_win);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
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
	sleep(1);
	close_mlx(mlx);
}
