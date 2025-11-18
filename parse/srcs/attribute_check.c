/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:38:03 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 18:58:28 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

// 1. used to check any float using range (float)
int	is_valid_float(char *s, float min, float max)
{
	if (!*s)
		return (0);
	if (!ft_isnum(*s) && !ft_issign(*s))
		return (0);
	if (ft_atof(s) < min || ft_atof(s) > max)
		return (0);
	if (ft_issign(*s))
		s++;
	if (!ft_isnum(*s))
		return (0);
	while (ft_isnum(*s))
		s++;
	if (*s == '.')
	{
		s++;
		if (!ft_isnum(*s))
			return (0);
		while (ft_isnum(*s))
			s++;
	}
	if (ft_issign(*s) || *s == '.')
		return (0);
	return (1);
}

// 2. used to check any int using range (int)
int	is_valid_int(char *s, int min, int max)
{
	int	val;

	if (!*s)
		return (0);
	if (!ft_isnum(*s) && !ft_issign(*s))
		return (0);
	val = ft_atoi(s);
	if (val < min || val > max)
		return (0);
	if (ft_issign(*s))
		s++;
	if (!ft_isnum(*s))
		return (0);
	while (ft_isnum(*s))
		s++;
	if (*s != '\0' && *s != '\n' && !ft_isspace(*s))
		return (0);
	return (1);
}

//3. rgb (int: 255,255,255)
int	is_valid_rgb(char *s)
{
	int	count;
	int	val;

	count = 0;
	while (count < 3)
	{
		if (!*s || !ft_isnum(*s))
			return (0);
		val = ft_atoi(s);
		if (val < 0 || val > 255)
			return (0);
		while (ft_isnum(*s))
			s++;
		if (count < 2)
		{
			if (*s != ',')
				return (0);
			s++;
		}
		count++;
	}
	if (*s != '\0' && *s != '\n' && !ft_isspace(*s))
		return (0);
	return (1);
}

// 4. point/vec, used to check any float XYZ using min/max (float)
int	is_valid_vec(char *s)
{
	int	j;

	j = 0;
	while (j < 3)
	{
		if (!is_valid_float(s, -FLT_MAX + 1, FLT_MAX - 1))
			return (0);
		while (ft_isnum(*s) || ft_issign(*s))
			s++;
		if (*s == '.' && ft_isnum(*(s + 1)))
		{
			s++;
			while (ft_isnum(*s))
				s++;
		}
		if (j < 2 && *s != ',')
			return (0);
		if (j < 2 && *s == ',')
			s++;
		j++;
	}
	if (*s != '\0' && *s != '\n' && !ft_isspace(*s))
		return (0);
	return (1);
}
