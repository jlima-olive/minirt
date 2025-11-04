/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/04 19:36:32 by jlima-so         ###   ########.fr       */
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
# include "my_libft/libft.h"

# ifndef HGT
#  define HGT 720.0
# endif

# ifndef AP_RAT
#  define AP_RAT 1/* (16.0 / 9) */
# endif

# ifndef FOV
#  define FOV 120
# endif

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
} t_vec;

typedef t_vec	t_rgb;
typedef t_vec	t_point;

typedef struct	s_ray
{
	t_point	ori;
	t_vec	dir;
	double	t;
}	t_ray;

typedef struct s_objinfo
{
	int		color;
	int		inside;
	int		light_count;
	t_vec	red_vec;
	t_point	point;
}	t_objinfo;

typedef struct s_lst
{
	struct s_lst	*next;
	void			*obj;
	char			id;
}	t_lst;

typedef struct s_sphere
{
	t_rgb	color;
	double	radius;
	t_point	center;
	t_point	p;
	t_vec	normal;
	char	type;
}	t_sphere;

typedef struct s_plane
{
	t_rgb	color;
	t_vec	norm;
	t_point	point;
	double	a;
	double	b;
	double	c;
	double	d;
	char	type;
}	t_plane;

typedef struct s_cylidner
{
	t_rgb	color;
	t_ray	ray;
	double	r;
	char	type;
}	t_cylidner;

typedef struct	s_simpleimg
{
	int		bpp;
	int		endian;
	int		line_len;
	void	*img_ptr;
	char	*pixel_ptr;
}	t_simpleimg;

typedef	struct s_light
{
	t_point			src;
	t_rgb			color;
	struct s_light	*next;
}	t_light;

typedef struct	s_mlximg
{
	int		total_lights;
	int		bpp;
	int		endian;
	int		line_len;
	double	ambient;
	void	*img_ptr;
	char	*pixel_ptr;
	t_point	camera;
	t_point	ctr_pnt;
	t_point	pixel00;
	t_vec	ori_vec;
	t_vec	del_h;
	t_vec	normal_h;
	t_vec	del_v;
	t_vec	normal_v;
	t_light	*ligh_rays;
	t_vec	min_vec;
	t_vec	vert;
	double	min_len;
	double	rad;
	double	deg;
	double	wdt;
	t_lst	*objs;
}	t_mlximg;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_mlximg	img;
	t_simpleimg	img2;
}   t_mlx;

int		my_button_hook(int key, t_mlx *mlx);
int		my_key_hook(int key, t_mlx *mlx);
int		close_mlx(t_mlx *mlx);

// replicating member functions
int			equal(t_point one, t_point two);
t_point		add(t_point one, t_point two);
t_point		sub(t_point one, t_point two);
t_point		mult(t_point point, double a);
t_point		set_class(double x, double y, double z);
int			get_rgb(t_point one, double a);
int			get_rgb_num(double r, double g, double b, double a);
t_ray		set_ray(t_point origin, t_vec direction);
t_vec		get_vector(t_mlximg img, double x, double y);
double		get_cos(t_vec a, t_vec b);
double		dot_product(t_vec a, t_vec b);
double		get_y(t_vec o, t_vec h);
t_vec		normalize_vec(t_vec vec);
double		vec_len(t_vec vec);
double		square_vec(t_vec vec);
double		vec_len(t_vec vec);
double		dot_product(t_vec a, t_vec b);
double		get_y(t_vec o, t_vec h);
double		get_x(t_vec h);
t_vec		normalize_vec(t_vec vec);
void 		get_objs(t_mlx *mlx);
t_lst		*new_lst(void);
t_sphere	*new_sphere(t_point center, double radius, t_rgb color);
t_ray		get_ray(t_mlximg img, double x, double y);
t_vec		new_vec(t_point a, t_point b);
double		div_product(t_vec a, t_vec b);
int			find_ligh(t_mlximg img, t_ray ray);

#endif