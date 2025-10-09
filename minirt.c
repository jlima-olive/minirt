/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 14:48:31 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(void *mlx)
{
	mlx = mlx_init();
	if (mlx == NULL)
		return (1);
	return (0);
}

void	close_mlx()
{
	
}

int	main(void)
{
	void	*mlx;
	
	mlx = NULL;
	if (init_mlx(mlx))
		return (1);
	close_mlx();
}
