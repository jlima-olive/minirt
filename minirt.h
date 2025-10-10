/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 13:04:28 by namejojo         ###   ########.fr       */
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
	t_point	fpixel;
	t_point	focus_point;
	t_vec	del_x;
	t_vec	del_y;
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

// replicating member functions
// arithmetic.c
t_point	add(t_point one, t_point two);
t_point	sub(t_point one, t_point two);
t_point	add(t_point one, t_point two);
int		equal(t_point one, t_point two);
t_point	mult_cords(t_point point, float a);
t_point	mult_vec(t_point point, float a);
t_point	mult_rgb(t_point point, float a);

t_point	set_class(float x, float y, float z);
int		get_color(t_rgb rgb);

#endif