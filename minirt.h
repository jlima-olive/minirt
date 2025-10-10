/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 11:09:51 by namejojo         ###   ########.fr       */
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

# ifndef HEIGHT
#  define HEIGHT 540
# endif

typedef struct	s_mlximg
{
	int		bpp;
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*pixel_ptr;
	t_point	camera;
	t_point	pixel;
}	t_mlximg;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_mlximg	img;
}   t_mlx;

typedef struct	s_vec
{
	float	x;
	float	y;
	float	z;
} t_vec;

typedef struct	s_ray
{
	t_point	point;
	t_vec	vec;
	float	t;
	t_point (*at)(t_ray);
} t_ray;

typedef t_vec	t_rgb;
typedef t_vec	t_point;

int		my_button_hook(int key, t_mlx *mlx);
int		my_key_hook(int key, t_mlx *mlx);
int		close_mlx(t_mlx *mlx);
t_point	get_cords(float x, float y, float z);

#endif