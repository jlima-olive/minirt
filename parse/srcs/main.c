/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:43:05 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/18 11:22:17 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
