/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:43:05 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	print_rgb(const t_rgb *c)
{
	printf("(%f, %f, %f)", c->x, c->y, c->z);
}

static void	print_vec(const t_vec *v)
{
	printf("(%.3f, %.3f, %.3f)", v->x, v->y, v->z);
}

void print_scene(const t_scene *scene)
{
    t_list *node;

    printf("----- SCENE DEBUG -----\n");

    if (scene->ambient)
    {
        printf("Ambient:\n");
        printf("  Ratio: %.3f\n", scene->ambient->ratio);
        printf("  Color: ");
        print_rgb(&scene->ambient->color);
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
        print_rgb(&scene->light->color);
        printf("\n");
    }
    else
        printf("Light: (null)\n");

    // Print spheres
    node = scene->list;
    while (node)
    {
        if (node->type == SPHERE)
        {
            t_sphere *sp = node->obj;
            printf("Sphere:\n");
            printf("  Center: ");
            print_vec(&sp->center);
            printf("\n  r: %.3f\n", sp->r);
            printf("  Color: ");
            print_rgb(&sp->color);
            printf("\n  Material: %d\n", sp->material);
        }
		if (node->type == PLANE)
        {
            t_plane *pl = node->obj;
            printf("Plane:\n");
            printf("  Point: ");
            print_vec(&pl->point);
            printf("\n  Normal: ");
        		print_vec(&pl->normal);
            printf("\n  Color: ");
            print_rgb(&pl->color);
            printf("\n  Material: %d\n", pl->material);
        }
		if (node->type == CYLINDER)
		{
			t_cylinder *cy = node->obj;
			printf("Cylinder:\n");
			printf("  Center: ");
			print_vec(&cy->center);
			printf("\n  Axis: ");
			print_vec(&cy->axis);
			printf("\n  r: %.3f\n", cy->r);
			printf("  Height: %.3f\n", cy->height);
			printf("  Color: ");
			print_rgb(&cy->color);
			printf("\n  Material: %d\n", cy->material);
		}
        node = node->next;
    }
	
    printf("-----------------------\n");
}


static void	init_scene(t_scene *scene)
{
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->list = NULL;
	scene->n_objects = 0;
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (!precheck(argc, argv[1]))
		return (1);
	init_scene(&scene);
	parse(argv[1], &scene);
	print_scene(&scene);
	clean_scene(&scene);
	return (0);
}
