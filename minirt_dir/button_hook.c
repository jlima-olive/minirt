/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:24:51 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 09:46:54 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int my_button_hook(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
		close_mlx(mlx);
	return (0);
}
