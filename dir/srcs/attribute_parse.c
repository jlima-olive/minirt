/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:00:15 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

//parse any float
float	parse_float(char *line, int *i)
{
	float	val;

	val = ft_atof(line + *i);
	if (ft_issign(line[*i]))
		(*i)++;
	while (ft_isnum(line[*i]))
		(*i)++;
	if (line[*i] == '.')
	{
		(*i)++;
		while (ft_isnum(line[*i]))
			(*i)++;
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	return (val);
}

int	parse_int(char *line, int *i)
{
	int	val;

	val = ft_atoi(line + *i);
	if (ft_issign(line[*i]))
		(*i)++;
	while (ft_isnum(line[*i]))
		(*i)++;
	while (ft_isspace(line[*i]))
		(*i)++;
	return (val);
}

//parse rgb
void	parse_color(char *line, int *i, t_rgb *color)
{
	int	val;

	val = ft_atoi(line + *i);
	color->x = val;
	while (ft_isnum(line[*i]))
		(*i)++;
	(*i)++;
	val = ft_atoi(line + *i);
	color->y = val;
	while (ft_isnum(line[*i]))
		(*i)++;
	(*i)++;
	val = ft_atoi(line + *i);
	color->z = val;
	while (ft_isnum(line[*i]))
		(*i)++;
	while (ft_isspace(line[*i]))
		(*i)++;
}

//parse any XYZ float point and vec
void	parse_vec(char *line, int *i, t_vec *vec)
{
	vec->x = parse_float(line, i);
	if (line[*i] == ',')
		(*i)++;
	vec->y = parse_float(line, i);
	if (line[*i] == ',')
		(*i)++;
	vec->z = parse_float(line, i);
}
