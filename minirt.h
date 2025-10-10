/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/11 00:30:49 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "mlx_linux/mlx_int.h"
# include "mlx_linux/mlx.h"

# ifndef HGT
#  define HGT 720
# endif

typedef struct	s_vec
{
	float	x;
	float	y;
	float	z;
} t_vec;

typedef t_vec	t_rgb;
typedef t_vec	t_point;

typedef struct	s_mlximg
{
	int		bpp;
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*pixel_ptr;
	t_point	camera;
	t_point	fpixel;
	t_point	ctr_pnt;
	t_point	ori_vec;
	t_point	pixel00;
	t_vec	del_h;
	t_vec	del_v;
	int		degres;
}	t_mlximg;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_mlximg	img;
}   t_mlx;

typedef struct	s_ray
{
	t_point	point;
	t_vec	vec;
	float	t;
	// t_point (*at)(t_ray);
} t_ray;

int		my_button_hook(int key, t_mlx *mlx);
int		my_key_hook(int key, t_mlx *mlx);
int		close_mlx(t_mlx *mlx);

// replicating member functions
int		equal(t_point one, t_point two);
t_point	add(t_point one, t_point two);
t_point	sub(t_point one, t_point two);
t_point	mult(t_point point, float a);
t_point	set_class(float x, float y, float z);
int		get_rgb(t_point one, float a);
int		get_rgb_num(float r, float g, float b, float a);

#endif