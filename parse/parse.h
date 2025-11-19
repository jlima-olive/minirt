/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:41:52 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/19 14:31:53 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// formatting check
typedef struct s_counts
{
	int				count_a;
	int				count_c;
	int				count_l;
	int				count_shape;
}					t_counts;

// helper structs

typedef struct s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef t_vec		t_rgb;
typedef t_vec		t_point;

typedef struct s_ray
{
	t_point			ori;
	t_vec			dir;
	double			t;
}					t_ray;

// scene elements
typedef struct s_ambient
{
	float			ratio;
	t_rgb			color;
}					t_ambient;

typedef struct s_camera
{
	t_vec			src;
	t_vec			dir;
	float			fov;
}					t_camera;

typedef struct s_light
{
	t_vec			src;
	float			brightness;
	t_rgb			color;
	struct s_light	*next;
}					t_light;

// shape structs

typedef struct s_sphere
{
	t_vec			center;
	float			r;
	t_rgb			color;
}					t_sphere;

typedef struct s_plane
{
	t_vec			point;
	t_vec			normal;
	t_rgb			color;
	double			a;
	double			b;
	double			c;
	double			d;
}					t_plane;

typedef struct s_cylidner
{
	t_vec			center;
	t_vec			axis;
	t_ray			ray;
	float			r;
	float			height;
	t_rgb			color;
}					t_cylinder;

// shapes list
typedef enum s_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE
}					t_obj_type;

typedef struct s_list
{
	t_obj_type		type;
	void			*obj;
	struct s_list	*next;
}					t_list;

// main scene struct
typedef struct s_scene
{
	t_ambient		*ambient;
	t_camera		*camera;
	t_light			*light;
	t_list			*list;
	int				n_objects;
}					t_scene;

// precheck
int					precheck(int argc, char *filename);

// clean
void				clean_scene(t_scene *scene);

// main parsing
void				parse(char *filename, t_scene *scene);

// utils
int					ft_isspace(int c);
int					ft_issign(int c);
int					isshape(char *sub);
int					ft_is_zerovec(t_vec *v);
int					count_attributes(char *line);

// attribute check
int					is_valid_float(char *s, float min, float max);
int					is_valid_int(char *s, int min, int max);
int					is_valid_vec(char *s);
int					is_valid_rgb(char *s);

// attribute parsing
float				parse_float(char *line, int *i);
int					parse_int(char *line, int *i);
void				parse_vec(char *line, int *i, t_vec *vec);
void				parse_color(char *line, int *i, t_rgb *color);

// element parsing
int					parse_ambient(char *line, t_scene *scene);
int					parse_camera(char *line, t_scene *scene);
int					parse_light(char *line, t_scene *scene);
int					parse_sphere(char *line, t_scene *scene);
int					parse_plane(char *line, t_scene *scene);
int					parse_cylinder(char *line, t_scene *scene);

t_ray				set_ray(t_point origin, t_vec direction);
t_point				mult(t_point point, double a);
