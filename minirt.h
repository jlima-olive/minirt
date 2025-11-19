/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:42:15 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/19 13:30:31 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include "my_libft/my_libft.h"
# include "parse/parse.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef HGT
#  define HGT 720.0
# endif

# ifndef AP_RAT
#  define AP_RAT 1 /* (16.0 / 9) */
# endif

# ifndef FOV
#  define FOV 120
# endif

typedef struct s_objinfo
{
	int			color;
	int			inside;
	int			light_count;
	t_vec		red_vec;
	t_point		point;
}				t_objinfo;

typedef struct s_simpleimg
{
	int			bpp;
	int			endian;
	int			line_len;
	void		*img_ptr;
	char		*pixel_ptr;
}				t_simpleimg;

typedef struct s_mlximg
{
	int			total_lights;
	int			bpp;
	int			endian;
	int			line_len;
	double		ambient;
	t_rgb		a_color;
	void		*img_ptr;
	char		*pixel_ptr;
	t_point		camera;
	t_point		ctr_pnt;
	t_point		pixel00;
	t_vec		ori_vec;
	t_vec		del_h;
	t_vec		normal_h;
	t_vec		del_v;
	t_vec		normal_v;
	t_light		*ligh_rays;
	t_vec		min_vec;
	t_vec		vert;
	double		min_len;
	double		fov;
	double		rad;
	double		deg;
	double		wdt;
	t_list		*objs;
	t_scene		*scene;
}				t_mlximg;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_mlximg	img;
	t_simpleimg	img2;
}				t_mlx;

int				my_button_hook(int key, t_mlx *mlx);
int				my_key_hook(int key, t_mlx *mlx);
int				close_mlx(t_mlx *mlx);

// replicating member functions
int				equal(t_point one, t_point two);
t_point			add(t_point one, t_point two);
t_point			sub(t_point one, t_point two);
t_point			set_class(double x, double y, double z);
int				get_rgb(t_point one, double a);
int				get_rgb_num(double r, double g, double b, double a);
t_vec			get_vector(t_mlximg img, double x, double y);
double			get_cos(t_vec a, t_vec b);
double			dot_product(t_vec a, t_vec b);
double			get_y(t_vec o, t_vec h);
t_vec			normalize_vec(t_vec vec);
double			vec_len(t_vec vec);
double			square_vec(t_vec vec);
double			vec_len(t_vec vec);
double			dot_product(t_vec a, t_vec b);
double			get_y(t_vec o, t_vec h);
double			get_x(t_vec h);
t_vec			normalize_vec(t_vec vec);
void			get_objs(t_mlx *mlx);
t_list			*new_lst(void);
t_sphere		*new_sphere(t_point center, double r, t_rgb color);
t_ray			get_ray(t_mlximg img, double x, double y);
t_vec			new_vec(t_point a, t_point b);
double			div_product(t_vec a, t_vec b);
int				find_ligh(t_mlximg img, t_ray ray);

double			get_cy_root(t_ray ray, t_cylinder *cy, double *dv, double *xv);
double			get_sp_root(t_sphere *sp, t_ray ray);
double			get_pl_root(t_ray ray, t_plane *pl);

t_objinfo		set_obj_info(void);

t_point			point_at(t_ray ray, double t);

int				get_true_rgb(t_mlximg img, t_rgb color, float root);

void			render(int x, int y, t_mlximg img);

t_rgb			get_negative_color(t_rgb color);

void			connect_parse(t_mlximg *img, t_scene scene);

t_mlximg		aux_parse(t_mlximg img);

void			run_code(t_mlx *mlx);

#endif