/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/09 16:17:39 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"

#ifndef WIDTH
# define WIDTH 1080
#endif

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
}   t_mlx;

typedef struct s_vec
{
    float	x;
    float	y;
    float	z;
} t_vec;

typedef t_vec t_rgb;
typedef t_vec t_point;

#endif