/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/19 11:46:40 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_random_vec(float min, float max)
{
	t_vec	ret;
	float	sqrd;
	float	len;

	while (1)
	{
		ret.x = ((float)rand() / RAND_MAX) * (max - min);
		ret.y = ((float)rand() / RAND_MAX) * (max - min);
		ret.z = ((float)rand() / RAND_MAX) * (max - min);
		sqrd = square_vec(ret);
		if (sqrd && sqrd <= 1)
			return (mult(ret, 1 / sqrt(sqrd)));
	}
}

void	free_obj(t_lst *obj)
{
	if (obj == NULL)
		return ;
	free(obj->obj);
	free_obj(obj->next);
	free(obj);
}

int	close_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free_obj(mlx->img.objs);
	exit (0);
	return (0);
}

int	init_mlx(t_mlx *mlx)
{
	t_mlximg	img;
	t_simpleimg	img2;

	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		close_mlx(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HGT * AP_RAT, HGT, "minirt");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * AP_RAT, HGT * AP_RAT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr
	= mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	mlx->img = img;
	if (img.pixel_ptr == NULL)
		close_mlx(mlx);

	img2.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * AP_RAT, HGT * AP_RAT);
	if (img2.img_ptr == NULL)
		close_mlx(mlx);
	img2.pixel_ptr
	= mlx_get_data_addr(img2.img_ptr, &img2.bpp, &img2.line_len, &img2.endian);
	mlx->img = img;
	if (img2.pixel_ptr == NULL)
		close_mlx(mlx);
	mlx->img2 = img2;
	return (0);
}

void	init_var(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

t_point	point_at(t_ray ray, float t)
{
	return (add(ray.ori, mult(ray.dir, t)));
}

t_vec	new_vec(t_point a, t_point b)
{
	return (sub(a, b));
}

t_objinfo	set_obj_info(void)
{
	t_objinfo	ret;

	ret.color = -1;
	ret.point = set_class(0, 0, 0);
	return (ret);
}

float	get_root(float a, float h, float c)
{
	float	root1;
	float	root2;

	root1 = h * h - a * c;
	if (root1 < 0)
		return (-1);
	root1 = sqrt(root1);
	root2 = (h - root1) / a;
	root1 = (h + root1) / a;
	return (ft_min_pos(root1, root2));
}

int	get_color_difu(t_point p, t_vec cp)
{
	t_vec	ran;
	float	prod;

	ran = get_random_vec(0, 1);
	prod = dot_product(ran, cp);
	ran = mult(ran, (prod > 0.0) - (prod <= 0.0));
}

t_objinfo	proven_hit_sphere(t_sphere *sp, t_ray ray, t_vec light)
{
	t_objinfo	info;
	t_vec		oc;
	t_vec		cp;
	float		a;
	float		h;
	float		c;
	float		root;

	info = set_obj_info();
	oc = sub(sp->center, ray.ori);
	a = dot_product(ray.dir, ray.dir);
	h = dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - (sp->radius * sp->radius);
	root = get_root(a, h, c);
	if (root < 0)
		return (info);
	info.point = point_at(ray, root);
	cp = mult(new_vec(info.point, sp->center), -1 / sp->radius);
	a = get_cos(cp, light);
	a = (a + 1) / 2;
	info.inside = dot_product(ray.dir, new_vec(info.point, sp->center)) > 0;
	printf("%d\n", info.inside);
	info.color = get_rgb(sp->color, a);
	get_rgb_num(1, 1, 1, a);
	// info.color = get_color_difu(info.point, cp);
	return (info);
}

t_objinfo	my_sphere_render1(t_sphere *sp, t_ray ray, t_vec light)
{
	t_objinfo	info;
	t_vec		oc;
	t_vec		op;
	float		a;
	float		b;
	float		c;
	float		sqr;
	float		res;

	info = set_obj_info();
	oc = sub(sp->center, ray.ori);
	a = dot_product(ray.dir, ray.dir);
	b = dot_product(mult(ray.dir, -2), oc);
	c = dot_product(oc, oc) - (sp->radius * sp->radius);
	sqr = b * b - 4 * a * c;
	if (sqr < 0)
		return (info);
	sqr = sqrt(sqr);
	res = (-b + sqr) / 2 * a;
	a = (-b - sqr) / 2 * a;
	if (a < 0 && res < 0)
		return (info);
	a = a * (a < res) + res * (res < a);
	info.point = point_at(ray, a);
	op = mult(new_vec(info.point, sp->center), 1 / sp->radius);
	a = get_cos(op, light);
	b = 1 - (a * (a > 0) - a * (a - 0));
	info.color = get_rgb_num(1, 1, 1, (1 - a) / 2);
	return (info);
}

t_vec	get_op_redirections1(t_vec vec, t_vec op)
{
	t_vec	ret;

	ret.x = 2 * vec.x + op.x; 
	ret.y = 2 * vec.y + op.y; 
	ret.z = 2 * vec.z + op.z; 
	return (ret);
}

int	get_color( t_mlximg img, float y, t_ray ray)
{
	t_objinfo	value;
	t_objinfo	new_v;
	t_lst		*lst;

	lst = img.objs;
	value = set_obj_info();
	while (lst)
	{
		if (lst->id == 's')
			new_v = my_sphere_render1(lst->obj, ray, img.ligh_ray);
		lst = lst->next;
		if (value.color == -1 || (new_v.color != -1
			&& vec_len(new_vec(img.camera, new_v.point))
			< vec_len(new_vec(img.camera, value.point))))
			value = new_v;
	}
	if (value.color != -1)
		return (value.color);
	y = y / HGT;
	return (get_rgb_num(0.5, 0.3, 0, y) + get_rgb_num(0.5, 0.7, 1, 1));
}

void	render(int x, int y, t_mlximg img, float ratio)
{
	int		offset;
	t_ray	ray;

	ray = get_ray(img, (int)(x / ratio), (int)(y / ratio));
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(img, (int)(y / ratio), ray);
}

t_rgb	decompose_color(unsigned color)
{
	t_rgb	ret;

	ret.x = color >> 16;
	ret.y = (color << 16) >> 24;
	ret.z = (color << 24) >> 24;
	return (ret);
}

void	get_medium_color(int x, int y, t_simpleimg img2, t_mlximg img)
{
	t_rgb	color;
	int		offset;

	offset = ((x - 1) * 4) + (y * img.line_len);
	color = decompose_color(*((unsigned int *)(img.pixel_ptr + offset)));
	offset = ((x + 1) * 4) + (y * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr + offset))));
	offset = (x * 4) + ((y + 1) * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr + offset))));
	offset = (x * 4) + ((y - 1) * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr + offset))));
	offset = (x * 4) + (y * img.line_len);
	color = add(color, decompose_color(*((unsigned int *)(img.pixel_ptr + offset))));
	color = mult(color, 1.0 / 5);
	*((unsigned int *)(img2.pixel_ptr + offset)) = get_rgb(color, 1.0 / 255);
}

void	anti_aliasing(t_simpleimg img2,t_mlximg img)
{
	float	w;
	float	h;
	float	x;
	float	y;
	float	var;
	float	ratio;

	ratio = AP_RAT;
	var = (HGT - HGT / ratio) / 2;
	w = HGT;
	h = HGT / ratio + var;
	y = var;
	w *= ratio;
	h *= ratio;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			get_medium_color(x, y, img2, img);
	}
}

void	run_code(t_mlx *mlx)
{
	float	w;
	float	h;
	float	x;
	float	y;
	float	var;
	float	ratio;

	ratio = AP_RAT;
	var = (HGT - HGT / ratio) / 2;
	w = HGT;
	h = HGT / ratio + var;
	y = var;
	w *= ratio;
	h *= ratio;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			render(x, y, mlx->img, ratio);
	}
	anti_aliasing(mlx->img2, mlx->img);
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, -var * ratio);
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img2.img_ptr, 0, -var * ratio);
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

t_ray	get_ray(t_mlximg img, float x, float y)
{
	t_ray	ray;
	t_vec	vec1;
	t_vec	vec2;
	t_vec	viewport_position;
	float	x1;
	float	y1;

	ray.ori = img.camera/* add(img.pixel00, mult(img.del_h, x)) */;
	// ray.ori = add(ray.ori, mult(img.del_v, y));
	// printf("n_vecpnt	%f %f %f\n",ray.ori.x,ray.ori.y,ray.ori.z);
	// printf("x = %f y = %f\n",x ,y);
	x = x / img.wdt - 0.5;
	y = y / HGT - 0.5;
	vec1 = mult(img.normal_h, sin(x * img.rad));
	vec2 = mult(img.normal_v, sin(y * img.rad));
	ray.dir = add(vec1, vec2);
	viewport_position = sub(img.ori_vec, ray.dir);
	x = ft_abs(x);
	y = ft_abs(y);
	x = (x * (x > y) + y * (y >= x));
	vec1 = img.min_vec;
	// printf("x = %f y = %f\n",x ,y);
	ray.dir = add(ray.dir, vec1);
	vec1 = mult(img.ori_vec, (cos(x * PI) * (1 - img.min_len)));
	ray.dir = add(ray.dir, vec1);
	return (ray);
}

t_mlximg parse(t_mlximg img)
{
	double	degree;
	double	asp_ratio;
	t_ray	vec;

	img.camera = set_class(0.0, 0.0, 0.0);	// done by the parser this is just an example
	img.ori_vec = set_class(0.0, 0.0, 1.0);	// done by the parser this is just an example
	degree = FOV;							// done by the parser this is just an example
	img.wdt = HGT;
	img.rad = ft_deg_to_rad(degree);
	if (img.rad == 0 || vec_len(img.ori_vec) == 0 /* check_stuff() */)
		exit/* _func */(1);
	img.ori_vec = normalize_vec(img.ori_vec);
	img.ctr_pnt = add(img.camera, img.ori_vec);
	img.del_h = set_class(img.ori_vec.z, 0, -img.ori_vec.x);
	img.del_h = add(img.del_h, mult(set_class(1, 0, 0), !vec_len(img.del_h)));
	img.del_h = mult(img.del_h, (sin(img.rad / 2) / img.wdt));
	img.normal_h = mult(img.del_h, img.wdt);
	img.del_v = set_class(get_x(img.del_h), get_y(img.ori_vec, img.del_h), 1);
	img.del_v = mult(edge_cases_del_v(img.ori_vec, img.del_v), sin(img.rad / 2) / HGT);
	img.normal_v = mult(img.del_v, HGT);
	printf("ori_vec	%f %f %f\n", img.ori_vec.x, img.ori_vec.y, img.ori_vec.z);
	printf("del_h	%f %f %f\n", img.del_h.x, img.del_h.y, img.del_h.z);
	printf("del_v	%f %f %f\n", img.del_v.x, img.del_v.y, img.del_v.z);
	printf("dot_product img.ori_vec, img.del_h = %f\n", dot_product(img.ori_vec, img.del_h));
	printf("dot_product img.ori_vec, img.del_v = %f\n", dot_product(img.ori_vec, img.del_v));
	printf("dot_product img.del_h,   img.del_v = %f\n", dot_product(img.del_h, img.del_v));
	img.pixel00 = add(img.ctr_pnt, mult(img.del_h, -img.wdt / 2));
	img.pixel00 = add(img.pixel00, mult(img.del_v, -HGT / 2));
	img.min_vec = mult(img.ori_vec, cos(img.rad / 2));
	img.min_len = vec_len(img.min_vec);
	printf("pixel00	%f %f %f\n\n\n", img.pixel00.x, img.pixel00.y, img.pixel00.z);
	vec = get_ray(img, img.wdt, 0);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	// printf("n_vecpnt	%f %f %f\n", vec.ori.x, vec.ori.y, vec.ori.z);
	vec = get_ray(img, img.wdt, HGT / 4);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	// printf("n_vecpnt	%f %f %f\n", vec.ori.x, vec.ori.y, vec.ori.z);
	vec = get_ray(img, img.wdt, HGT / 2);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	// printf("n_vecpnt	%f %f %f\n", vec.ori.x, vec.ori.y, vec.ori.z);
	vec = get_ray(img, img.wdt, 3 * HGT / 4);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	// printf("n_vecpnt	%f %f %f\n", vec.ori.x, vec.ori.y, vec.ori.z);
	vec = get_ray(img, img.wdt, HGT);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	// printf("n_vecpnt	%f %f %f\n", vec.ori.x, vec.ori.y, vec.ori.z);
	// exit(0);
	return (img);
}

int	main(void)
{
	t_mlx	mlx;
	t_point	camera_center;
	t_point	pixel;

	// if (HGT != 720)
		// return (1);
	init_var(&mlx);
	if (init_mlx(&mlx))
		return (1);
	mlx.img = parse(mlx.img);
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, ButtonPress, ButtonPressMask, my_button_hook, &mlx);
	get_objs(&mlx);
	run_code(&mlx);
	mlx_loop(mlx.mlx_ptr);
	close_mlx(&mlx);
}
