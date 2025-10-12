/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/12 20:33:33 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit (0);
}

int	init_mlx(t_mlx *mlx)
{
	t_mlximg	img;

	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		close_mlx(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HGT * 16 / 9, HGT, "minirt");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * 16/9, HGT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr
	= mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	mlx->img = img;
	if (img.pixel_ptr == NULL)
		close_mlx(mlx);
	return (0);
}

void	init_var(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

int	hit_sphere1(t_point center, double radius, t_ray ray)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	sqr;

	oc = sub(center, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = dot_product(mult(ray.direction, -2), oc);
	c = dot_product(oc, oc) - (radius * radius);
	sqr = b * b - 4 * a * c;
	return (sqr > 0);
}

int	hit_sphere2(t_point center, double radius, t_ray ray)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	ok;
	float	ck;
	float	res;
	float	sqr;

	
	sqr = b * b - 4 * a * c;
	return (sqr > 0);
}

int	get_color(float y, t_ray ray)
{
	if (hit_sphere1(set_class(0, 0, 1), 0.5, ray))
		return (get_rgb_num(1, 0 ,0, 1));
	if (hit_sphere2(set_class(0, 0, 1), 0.5, ray))
		return (get_rgb_num(1, 0 ,0, 1));
	y = y / HGT;
	return (get_rgb_num(0.5, 0.3, 0, y) + get_rgb_num(0.5, 0.7, 1, 1));
}

void	render(int x, int y, t_mlximg img)
{
	int		offset;
	t_ray	ray;

	ray = set_ray(img.camera, get_vector(img, x, y));
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(y, ray);
}

void	paint_back_ground(t_mlx *mlx)
{
	int	w;
	int	x;
	int	y;

	w = HGT * 16 / 9;
	y = -1;
	while (++y < HGT)
	{
		x = -1;
		while (++x < w)
			render(x, y, mlx->img);
	}
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
}
/* 
void	my_pixel_put(int x, int y, t_mlximg img)
{
	int	offset;
	
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(y);
}

void	run_code(t_mlx *mlx)
{
	int	w;
	int	x;
	int	y;

	w = HGT * 16 / 9;
	y = -1;
	while (++y < HGT)
	{
		x = -1;
		while (++x < w)
			my_pixel_put(x, y, mlx->img);
	}
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
} */

double	vec_len(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec	normalize_vec(t_vec vec)
{
	return (mult(vec, 1 / vec_len(vec)));
}

double	get_x(t_vec h)
{
	return (-h.z / h.x);
}

double	get_y(t_vec o, t_vec h)
{
	return ((h.z * o.x - o.z * h.x) / (o.y * h.x));
}

double	dot_product(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double get_cos(t_vec a, t_vec b)
{
	float	len;

	len = (vec_len(a) * vec_len(b));
	return (dot_product(a, b) / len);
}

t_vec edge_cases_del_v(t_vec o, t_vec v)
{
	if (o.z == 0)
		return (set_class(-o.y, o.x, 0));
	if (o.y == 0)
		return (set_class(0, -1 ,0));
	return (v);
}

t_vec	get_vector(t_mlximg img, float x, int y)
{
	t_vec	vec;

	vec = add(img.pixel00, mult(img.del_h, x));
	vec = add(vec, mult(img.del_v, y));
	// printf("%f %f\n", x, img.rad / 2);
	x = (x - (img.wdt / 2)) / img.wdt * 2;
	x = (x > 0) * x - x * (x < 0);
	// printf("%f\n", x);
	// vec = add(vec, mult(img.ori_vec, -sin(x * img.rad / 2)));
	return (vec);
} 

t_mlximg parse(t_mlximg img)
{
	double	degree;
	double	cos;
	double	z;
	t_vec	vec;

	img.wdt = HGT * 16 / 9;
	img.camera = set_class(0.0, 0.0, 0.0);	// done by the parser this is just an example
	img.ori_vec = set_class(0.0, 0.0, 1.0);	// done by the parser this is just an example
	degree = 180.0;							// done by the parser this is just an example
	img.rad = degree / 180 * 3.14159265359;
	if (img.rad == 0 || vec_len(img.ori_vec) == 0 /* check_stuff() */)
		exit/* _func */(1);
	img.ori_vec = normalize_vec(img.ori_vec);
	img.ctr_pnt = add(img.camera, img.ori_vec);
	img.del_h = set_class(img.ori_vec.z, 0, -img.ori_vec.x);
	img.del_h = add(img.del_h, mult(set_class(1, 0, 0), !vec_len(img.del_h)));
	img.del_h = mult(img.del_h, (2.0 * sin(img.rad / 2)) / img.wdt);
	img.del_v = set_class(get_x(img.del_h), get_y(img.ori_vec, img.del_h), 1); 
	img.del_v = mult(edge_cases_del_v(img.ori_vec, img.del_v), 2.0 / HGT);
	printf("ori_vec	%f %f %f\n", img.ori_vec.x, img.ori_vec.y, img.ori_vec.z);
	printf("del_h	%f %f %f\n", img.del_h.x, img.del_h.y, img.del_h.z);
	printf("del_v	%f %f %f\n", img.del_v.x, img.del_v.y, img.del_v.z);
	printf("dot_product img.ori_vec, img.del_h = %f\n", dot_product(img.ori_vec, img.del_h));
	printf("dot_product img.ori_vec, img.del_v = %f\n", dot_product(img.ori_vec, img.del_v));
	printf("dot_product img.del_h,   img.del_v = %f\n", dot_product(img.del_h, img.del_v));
	img.pixel00 = add(img.ctr_pnt, mult(img.del_h, -img.wdt / 2));
	img.pixel00 = add(img.pixel00, mult(img.del_v, -HGT / 2));
	vec = get_vector(img, img.wdt, HGT);
	printf("pixel00	%f %f %f\n", img.pixel00.x, img.pixel00.y, img.pixel00.z);
	printf("n_vec	%f %f %f\n", vec.x, vec.y, vec.z);
	return (img);
}

int	main(void)
{
	t_mlx	mlx;
	t_point	camera_center;
	t_point	pixel;

	if (HGT != 720)
		return (1);
	init_var(&mlx);
	if (init_mlx(&mlx))
		return (1);
	mlx.img = parse(mlx.img);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, ButtonPress, ButtonPressMask, my_button_hook, &mlx);
	paint_back_ground(&mlx);
	
	// run_code(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
