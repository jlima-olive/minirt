/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:00:26 by psantos-          #+#    #+#             */
/*   Updated: 2025/11/17 23:35:43 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	parse_fraction(const char *s, float *frac)
{
	float	divisor;

	divisor = 10.0;
	*frac = 0.0;
	if (*s != '.')
		return ;
	s++;
	while (*s >= '0' && *s <= '9')
	{
		*frac += (*s - '0') / divisor;
		divisor *= 10.0;
		s++;
	}
}

float	ft_atof(char *s)
{
	int		sign;
	float	result;
	float	frac;

	sign = 1;
	result = 0.0;
	frac = 0.0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = result * 10.0 + (*s++ - '0');
	parse_fraction(s, &frac);
	result = sign * (result + frac);
	if (result > FLT_MAX)
		return (FLT_MAX);
	if (result < -FLT_MAX)
		return (-FLT_MAX);
	return ((float)result);
}
