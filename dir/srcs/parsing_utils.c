/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:38:15 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t');
}

int	ft_issign(int c)
{
	return (c == '+' || c == '-');
}

int	isshape(char *sub)
{
	return (!ft_strncmp(sub, "sp", 2)
		|| !ft_strncmp(sub, "pl", 2)
		|| !ft_strncmp(sub, "cy", 2));
}

int	ft_is_zerovec(t_vec *v)
{
	return (v->x == 0.0f && v->y == 0.0f && v->z == 0.0f);
}

int	count_attributes(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && line[i] != '\n')
		{
			count++;
			while (line[i] && !ft_isspace(line[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}
