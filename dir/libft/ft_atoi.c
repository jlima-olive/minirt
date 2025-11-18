/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 01:46:47 by psantos-          #+#    #+#             */
/*   Updated: 2025/10/27 10:07:30 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	number;

	number = 0;
	sign = 1;
	while ((*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9') && *str)
	{
		number = (number * 10) + (*str - '0');
		if (sign * number > INT_MAX)
			return (INT_MAX);
		if (sign * number < INT_MIN)
			return (INT_MIN);
		str++;
	}
	return ((int)(number * sign));
}
