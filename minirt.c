/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:56 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/19 13:34:07 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static void	print_color(const t_rgb *c)
{
	printf("(%f, %f, %f)", c->x, c->y, c->z);
}

static void	print_vec(const t_vec *v)
{
	printf("(%.3f, %.3f, %.3f)", v->x, v->y, v->z);
}

void	print_scene(const t_scene *scene)
{
	t_list		*node;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	printf("----- SCENE DEBUG -----\n");
	if (scene->ambient)
	{
		printf("Ambient:\n");
		printf("  Ratio: %.3f\n", scene->ambient->ratio);
		printf("  Color: ");
		print_color(&scene->ambient->color);
		printf("\n");
	}
	else
		printf("Ambient: (null)\n");
	if (scene->camera)
	{
		printf("Camera:\n");
		printf("  Position: ");
		print_vec(&scene->camera->src);
		printf("\n  Direction: ");
		print_vec(&scene->camera->dir);
		printf("\n  FOV: %.2f\n", scene->camera->fov);
	}
	else
		printf("Camera: (null)\n");
	if (scene->light)
	{
		printf("Light:\n");
		printf("  Position: ");
		print_vec(&scene->light->src);
		printf("\n  Brightness: %.3f\n", scene->light->brightness);
		printf("  Color: ");
		print_color(&scene->light->color);
		printf("\n");
	}
	else
		printf("Light: (null)\n");
	node = scene->list;
	while (node)
	{
		if (node->type == SPHERE)
		{
			sp = node->obj;
			printf("Sphere:\n");
			printf("  Center: ");
			print_vec(&sp->center);
			printf("\n  r: %.3f\n", sp->r);
			printf("  Color: ");
			print_color(&sp->color);
			printf("\n  Material: %d\n", sp->material);
		}
		if (node->type == PLANE)
		{
			pl = node->obj;
			printf("Plane:\n");
			printf("  Point: ");
			print_vec(&pl->point);
			printf("\n  Normal: ");
			print_vec(&pl->normal);
			printf("\n  Color: ");
			print_color(&pl->color);
			printf("\n  a: %f\n", pl->a);
			printf("  b: %f\n", pl->b);
			printf("  c: %f\n", pl->c);
			printf("  d: %f\n", pl->d);
		}
		if (node->type == CYLINDER)
		{
			cy = node->obj;
			printf("Cylinder:\n");
			printf("  Center: ");
			print_vec(&cy->ray.ori);
			printf("\n  Axis: ");
			print_vec(&cy->ray.dir);
			printf("\n  r: %.3f\n", cy->r);
			printf("  Height: %.3f\n", cy->height);
			printf("  Color: ");
			print_color(&cy->color);
			printf("\n  Material: %d\n", cy->material);
		}
		node = node->next;
	}
	printf("-----------------------\n");
} */
int	close_mlx(t_mlx *mlx)
{
	clean_scene(mlx->img.scene);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
	return (0);
}

int	init_mlx(t_mlx *mlx)
{
	t_mlximg	img;

	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		close_mlx(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx_ptr, HGT * AP_RAT, HGT, "minirt");
	if (mlx->mlx_win == NULL)
		close_mlx(mlx);
	img.img_ptr = mlx_new_image(mlx->mlx_ptr, HGT * AP_RAT, HGT);
	if (img.img_ptr == NULL)
		close_mlx(mlx);
	img.pixel_ptr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len,
			&img.endian);
	mlx->img = img;
	if (img.pixel_ptr == NULL)
		close_mlx(mlx);
	mlx->img = img;
	return (0);
}

void	init_var(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->mlx_win = NULL;
}

static void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->list = NULL;
	scene->n_objects = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_scene	scene;

	if (AP_RAT < 1)
		return (write(2, "Invalid aspect ratio\n", 22));
	if (!precheck(argc, argv[1]))
		return (1);
	init_scene(&scene);
	parse(argv[1], &scene);
	init_var(&mlx);
	if (init_mlx(&mlx))
		return (1);
	connect_parse(&(mlx.img), scene);
	mlx.img = aux_parse(mlx.img);
	mlx.img.scene = &scene;
	scene.list = mlx.img.objs;
	mlx_hook(mlx.mlx_win, 17, 0l, close_mlx, &mlx);
	mlx_hook(mlx.mlx_win, KeyPress, KeyPressMask, my_key_hook, &mlx);
	run_code(&mlx);
	mlx_loop(mlx.mlx_ptr);
	close_mlx(&mlx);
}
