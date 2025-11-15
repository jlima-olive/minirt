/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/04 21:31:44 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_random_vec(double min, double max)
{
	t_vec	ret;
	double	sqrd;
	double	len;

	while (1)
	{
		ret.x = ((double)rand() / RAND_MAX) * (max - min);
		ret.y = ((double)rand() / RAND_MAX) * (max - min);
		ret.z = ((double)rand() / RAND_MAX) * (max - min);
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
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * AP_RAT, HGT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr
	= mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	mlx->img = img;
	if (img.pixel_ptr == NULL)
		close_mlx(mlx);

	img2.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * AP_RAT, HGT);
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

t_point	point_at(t_ray ray, double t)
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

	ret.light_count = 0;
	ret.color = -1;
	ret.point = set_class(0, 0, 0);
	ret.red_vec = set_class(0, 0, 0);
	return (ret);
}

double	proven_get_root(double a, double h, double c)
{
	double	root1;
	double	root2;

	root1 = h * h - a * c;
	if (root1 < 0)
		return (-1);
	root1 = sqrt(root1);
	root2 = (h - root1) / a;
	root1 = (h + root1) / a;
	return (ft_min_pos(root1, root2));
}

double	get_pl_root(t_ray ray, t_plane *pl)
{
	double	denominator;
	double	nominator;
	double	ret;

	if (dot_product(ray.dir, pl->norm) < 0.0001)
		return (-1);
	nominator =
		-pl->d - pl->a * ray.ori.x - pl->b * ray.ori.y - pl->c * ray.ori.z;
	denominator = pl->a * ray.dir.x + pl->b * ray.dir.y + pl->c * ray.dir.z;
	ret = nominator / denominator;
	if (ret != ret)
		return (-1);
	return (ret);
}

int	get_color_difu(t_point p, t_vec cp)
{
	t_vec	ran;
	double	prod;

	ran = get_random_vec(0, 1);
	prod = dot_product(ran, cp);
	ran = mult(ran, (prod >= 0.0) - (prod < 0.0));
	// return ();
}

t_objinfo	proven_hit_sphere(t_mlximg img, t_sphere *sp, t_ray ray, t_light *light)
{
	t_objinfo	info;
	t_vec		oc;
	t_vec		cp;
	double		a;
	double		h;
	double		c;
	double		root;
	double		len;

	info = set_obj_info();
	oc = sub(sp->center, ray.ori);
	a = dot_product(ray.dir, ray.dir);
	h = dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - (sp->radius * sp->radius);
	root = proven_get_root(a, h, c);
	if (root < 0)
		return (info);
	info.point = point_at(ray, root);
	cp = mult(new_vec(info.point, sp->center), -1 / sp->radius);
	a = get_cos(cp, new_vec(info.point, light->src));
	// a = (a + 1) / 2;
	a = a * a ;
	// len = vec_len(new_vec(info.point, light->src));
	// a = a / len / len * 100;
	if (a > 1)
		a = 1;
	info.inside = dot_product(ray.dir, new_vec(info.point, sp->center)) > 0;
	// printf("%d\n", info.inside);
	// info.color = get_rgb(sp->color, a);
	info.color = get_rgb_num(1, 1, 1, a);
	// info.color = get_color_difu(info.point, cp);
	return (info);
}

t_objinfo	my_sphere_render1(t_sphere *sp, t_ray ray, t_vec light)
{
	t_objinfo	info;
	t_vec		oc;
	t_vec		op;
	double		a;
	double		b;
	double		c;
	double		sqr;
	double		res;

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

t_objinfo	hit_plane(t_mlximg img, t_plane *pl, t_ray ray, t_light *light)
{
	t_vec		pl_light;
	t_vec		pla;
	t_objinfo	info;
	double		root;
	double		len;

	root = get_pl_root(ray, pl);
	if (root < 0 || root > 100000)
		return (info.color = -1, info);
	info = set_obj_info();
	info.point = point_at(ray, root);
	pl_light = new_vec(info.point, light->src);
	root = get_cos(pl->norm, pl_light);
	if (root < img.ambient)
		root = img.ambient;
	// root = 1 * (root > 1) + img.ambient * (root < img.ambient) + root * (root > 0 && root < 1);
	ray = set_ray(info.point, mult(pl_light, -1));
	if (find_ligh(img, ray))
		root = img.ambient;
	info.color = get_rgb(pl->color, root);
	return (info);
}

double	root_pl_plane(t_ray ray, t_plane *pl)
{
	double	denominator;
	double	nominator;
	double	ret;

	if (dot_product(ray.dir, pl->norm) < 0.0001)
		return (-1);
	nominator =
		-pl->d - pl->a * ray.ori.x - pl->b * ray.ori.y - pl->c * ray.ori.z;
	denominator = pl->a * ray.dir.x + pl->b * ray.dir.y + pl->c * ray.dir.z;
	ret = nominator / denominator;
	if (ret != ret)
		return (-1);
	return (ret);
}

double	get_sp_root(t_sphere *sp, t_ray ray)
{
	t_vec		oc;
	double		root1;
	double		root2;
	double			a;
	double			h;
	double			c;

	oc = sub(sp->center, ray.ori);
	a = dot_product(ray.dir, ray.dir);
	h = dot_product(ray.dir, oc);
	c = dot_product(oc, oc) - (sp->radius * sp->radius);
	root1 = h * h - a * c;
	if (root1 < 0)
		return (-1);
	root1 = sqrt(root1);
	root2 = (h - root1) / a;
	root1 = (h + root1) / a;
	return (ft_min_pos(root1, root2));
}
/*  */

t_objinfo	hit_sphere(t_mlximg img, t_sphere *sp, t_ray ray, t_light *light)
{
	t_light		*walk;
	t_objinfo	info;
	t_vec		pl;
	t_vec		cp;
	double		root;
	double		new_root;
	double		len;
	int			sign;

	root = get_sp_root(sp, ray);
	if (root < 0)
		return (info.color = -1, info);
	info = set_obj_info();
	info.point = point_at(ray, root);
	cp = mult(new_vec(info.point, sp->center), -1 / sp->radius);
	walk = light;
	root = 0;
	while (walk != NULL)
	{
		len = vec_len(new_vec(info.point, light->src));
		pl =  new_vec(info.point, walk->src);
		root = get_cos(cp, pl);
		walk = walk->next;
	}
	if (root < img.ambient)
		root = img.ambient;
	ray = set_ray(info.point, mult(pl, -1));
	if (find_ligh(img, ray))
		root = img.ambient;
	info.color = get_rgb(sp->color, root);
	return (info);
}

double	get_cy_root(t_ray ray, t_cylidner *cy, double *dv, double *xv)
{
	t_vec	x;
	double	a;
	double	b;
	double	c;
	double	outside;
	double	root;

	x = new_vec(ray.ori, cy->ray.ori);
	*dv = dot_product(ray.dir, cy->ray.dir);
	*xv = dot_product(x, cy->ray.dir);
	a = dot_product(ray.dir, ray.dir) - *dv * *dv;
	if (a == 0)
		return (-1);
	b = 2 * (dot_product(ray.dir, x) - *dv * *xv);
	c = dot_product(x, x) - *xv * *xv - cy->r * cy->r;
	root = b * b -4 * a * c;
	if (root < 0)
		return (-1);
	root = sqrt(root);
	root = root / (a * 2);
	b = -b / (a * 2);
	return (ft_min_pos(b - root, b + root));
}

double	get_k(t_vec dir, t_vec pb)
{
	return (dot_product(dir, pb) / square_vec(dir));
}

float	get_lreflect(t_point pt, t_vec norm, t_vec dir, t_light light)
{
	t_ray		ray;
	t_point		temp;
	t_vec		lreflect;
	t_vec		p_light;
	float		cosv;
	float		sinv;
	float		root;
	t_sphere	sp;

	ray.ori = pt;
	ray.dir = dir;
	temp = point_at(ray, 1);
	cosv = get_cos(norm, dir);
	lreflect = mult(dir, -1);
	if (cosv != 0)
	{
		sinv = sqrt(1 - cosv * cosv);
		temp = add(temp, mult(norm, sinv * 2));
		lreflect = sub(temp, pt);
	}
	p_light = sub(light.src, pt);
	sp.center = light.src;
	sp.radius = 5.0;
	ray.ori = pt;
	ray.dir = lreflect;
	root = get_sp_root(&sp, ray);
	if (root <= 0)
		return (0);
/********************** */
	t_point	inter;
	t_vec	cp;
	t_light	walk;

	inter = point_at(ray, root);
	cp = mult(new_vec(inter, sp.center), -1 / sp.radius);
	root = get_cos(cp, lreflect);
	root = (root + 9) / 10;
/********************** */
	return (root);
}

t_objinfo	hit_cylinder(t_mlximg img, t_cylidner *cy, t_ray ray, t_light *light)
{
	t_light		*walk;
	t_objinfo	info;
	t_point		center;
	t_vec		cp;
	t_rgb		color;
	double		root;
	double		k;
	double		dv;
	double		xv;
	t_vec		pl_light;
	double		ref;

	root = get_cy_root(ray, cy, &dv, &xv);
	if (root < 0)
		return (info.color = -1, info);
	info = set_obj_info();
	info.point = point_at(ray, root);
	k = dv * root + xv;
	center = point_at(cy->ray, k);
	cp = new_vec(info.point, center);
	pl_light = new_vec(light->src, info.point);
	// ref = get_lreflect(info.point, cp, ray.dir, *light);
	root = get_cos(pl_light, cp);
	if (root < img.ambient)
		root = img.ambient;
	// root = 1 * (root > 1) + img.ambient * (root < img.ambient) + root * (root > 0 && root < 1);
	color = cy->color;
	// if (ref)
	// {
		// color = light->color;
		// root = ref;
	// }
	ray = set_ray(info.point, mult(pl_light, 1));
	if (find_ligh(img, ray))
		root = img.ambient;
	info.color = get_rgb(color, root);
	return (info); 
}

int	get_color( t_mlximg img, double y, t_ray ray)
{
	t_objinfo	value;
	t_objinfo	new_v;
	t_lst		*lst;
	double		len;

	lst = img.objs;
	value = set_obj_info();
	while (lst)
	{
		if (lst->id == 's')
			new_v = hit_sphere(img, lst->obj, ray, img.ligh_rays);
		else if (lst->id == 'p')
			new_v = hit_plane(img, lst->obj, ray, img.ligh_rays);
		else if (lst->id == 'c')
			new_v = hit_cylinder(img, lst->obj, ray, img.ligh_rays);
		len = vec_len(new_vec(img.camera, new_v.point));
		if (value.color == -1 || (new_v.color != -1 && len
			< vec_len(new_vec(img.camera, value.point))))
			value = new_v;
		lst = lst->next;
	}
	if (value.color != -1)
		return (value.color);
	y = y / HGT;
	return (get_rgb_num(0.5, 0.3, 0, y) + get_rgb_num(0.5, 0.7, 1, 1));
}

void	render(int x, int y, t_mlximg img)
{
	int		offset;
	t_ray	ray;

	ray = get_ray(img, (int)(x), (int)(y));
	offset = (x * 4) + (y * img.line_len);
	*((unsigned int *)(img.pixel_ptr + offset))
	= get_color(img, (int)(y), ray);
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
	double	w;
	double	h;
	double	x;
	double	y;

	w = HGT * AP_RAT;
	h = HGT;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			get_medium_color(x, y, img2, img);
	}
}

void	run_code(t_mlx *mlx)
{
	double	w;
	double	h;
	double	x;
	double	y;

	w = HGT * AP_RAT;
	h = HGT;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
			render(x, y, mlx->img);
	}
	// anti_aliasing(mlx->img2, mlx->img);
	mlx_put_image_to_window
	(mlx->mlx_ptr, mlx->mlx_win, mlx->img.img_ptr, 0, 0);
	// mlx_put_image_to_window
	// (mlx->mlx_ptr, mlx->mlx_win, mlx->img2.img_ptr, 0, 0);
}

double	get_cos(t_vec a, t_vec b)
{
	double	len;

	len = (vec_len(a) * vec_len(b));
	return (dot_product(a, b) / len);
}

t_vec	edge_cases_del_v(t_vec o, t_vec v)
{
	if (o.y == 0)
		return (set_class(0, -1 ,0));
	if (o.x == 0 && o.z == 0)
		return (set_class(0, 0, 1));
	if (o.x == 0)
	{
		if (o.z > 0)
			return (normalize_vec(set_class(0, -o.z, o.y)));
		else
			return (normalize_vec(set_class(0, o.z, -o.y)));
	}
	if (o.z == 0)
	{
		if (o.x < 0)
			return (normalize_vec(set_class(-o.y, o.x, 0)));
		else
			return (normalize_vec(set_class(o.y, -o.x, 0)));
	}
	if (v.y > 0)
		v = mult(v, -1);
	return (normalize_vec(v));
}

t_ray	get_ray(t_mlximg img, double x, double y)
{
	t_ray	ray;
	t_vec	vp_position;
	double	cl;

	if (x == 0 && FOV == 180)
		return (set_ray(img.camera, sub(img.camera, mult(img.del_h, -1))));
	if (x == img.wdt && FOV == 180)
		return (set_ray(img.camera, sub(img.camera, mult(img.del_h, 1))));
	if (FOV > 120)
		cl = (img.deg - 120) / 60;
	
	ray.ori = img.camera;
	vp_position = add(img.pixel00, mult(img.del_h, x));
	vp_position = add(vp_position, mult(img.del_v, y));
	ray.dir = normalize_vec(new_vec(vp_position, ray.ori));
	return (ray);
}

t_mlximg parse(t_mlximg img)
{
	double	vp_size;
	double	sinv;
	double	cosv;
	t_ray	vec;

	img.camera = set_class(-5.0, 7.5, -10.0);	// done by the parser this is just an example
	img.ori_vec = set_class(1.0, -1.0, 1);		// done by the parser this is just an example
	img.wdt = HGT * AP_RAT;
	img.deg = FOV * (FOV <= 179.99999) + 179.99999 * (FOV > 179.99999);
	img.rad = ft_deg_to_rad(img.deg);
	if (img.rad == 0 || vec_len(img.ori_vec) == 0 /* || check_stuff() */)
		exit/* _func */(1);
	img.ori_vec = normalize_vec(img.ori_vec);
	img.ctr_pnt = add(img.camera, img.ori_vec);
	img.del_h = set_class(img.ori_vec.z, 0, -img.ori_vec.x);
	img.del_h = add(img.del_h, mult(set_class(1, 0, 0), !vec_len(img.del_h)));
	vp_size = 2 * tan(img.rad / 2);
	img.del_h = mult(normalize_vec(img.del_h), vp_size / img.wdt);
	img.normal_h = mult(img.del_h, img.wdt);
	img.del_v = set_class(get_x(img.del_h), get_y(img.ori_vec, img.del_h), 1);
	img.del_v = mult(edge_cases_del_v(img.ori_vec, img.del_v), (vp_size / AP_RAT) / HGT);
	printf("ori_vec	%f %f %f\n", img.ori_vec.x, img.ori_vec.y, img.ori_vec.z);
	printf("del_h	%f %f %f\n", img.del_h.x, img.del_h.y, img.del_h.z);
	printf("del_v	%f %f %f\n", img.del_v.x, img.del_v.y, img.del_v.z);
	printf("dot_product img.ori_vec, img.del_h = %f\n", dot_product(img.ori_vec, img.del_h));
	printf("dot_product img.ori_vec, img.del_v = %f\n", dot_product(img.ori_vec, img.del_v));
	printf("dot_product img.del_h,   img.del_v = %f\n", dot_product(img.del_h, img.del_v));
	img.pixel00 = add(img.ctr_pnt, mult(img.del_h, -img.wdt / 2));
	img.pixel00 = add(img.pixel00, mult(img.del_v, -HGT / 2));
	printf("pixel00	%f %f %f\n", img.pixel00.x, img.pixel00.y, img.pixel00.z);
	vec = get_ray(img, 0, 0);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	vec = get_ray(img, img.wdt / 4, HGT / 4);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	vec = get_ray(img, img.wdt / 2, HGT / 2);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	vec = get_ray(img, 3 * img.wdt / 4, 3 * HGT / 4);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	vec = get_ray(img, img.wdt, HGT);
	printf("n_vecdir	%f %f %f\n", vec.dir.x, vec.dir.y, vec.dir.z);
	return (img);
}

int	find_ligh(t_mlximg img, t_ray ray)
{
	double	len;
	double	var1;
	double	var2;
	t_lst	*lst;

	lst = img.objs;
	while (lst)
	{
		if (lst->id == 's')
			len = get_sp_root(lst->obj, ray);
		else if (lst->id == 'p')
			len = get_pl_root(ray, lst->obj);
		else if (lst->id == 'c')
			len = get_cy_root(ray, lst->obj, &var1, &var2);
		if (len > 0.00000001 && len < 0.9999999)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	main(void)
{
	t_mlx	mlx;
	t_point	camera_center;
	t_point	pixel;

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
