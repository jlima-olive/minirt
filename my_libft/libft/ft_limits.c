/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:46:43 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/16 16:21:26 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_max(float a, float b)
{
	return (a * (a > b) - b * (b >= a));
}

float	ft_min(float a, float b)
{
	return (a * (a < b) - b * (b <= a));
}

float	ft_max_neg(float a, float b)
{
	if (a > 0 && b > 0)
		return (-1);
	if (a > 0)
		return (b);
	if (b > 0)
		return (a);
	return (a * (a > b && a < 0) + b * (b >= a && b < 0));
}

float	ft_min_pos(float a, float b)
{
	if (a < 0 && b < 0)
		return (-1);
	if (a < 0)
		return (b);
	if (b < 0)
		return (a);
	return (a * (a < b) + b * (b <= a));
}
