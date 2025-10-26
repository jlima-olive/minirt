/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:46:43 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/26 18:48:13 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_max(double a, double b)
{
	return (a * (a > b) - b * (b >= a));
}

double	ft_min(double a, double b)
{
	return (a * (a < b) - b * (b <= a));
}

double	ft_max_neg(double a, double b)
{
	if (a > 0 && b > 0)
		return (-1);
	if (a > 0)
		return (b);
	if (b > 0)
		return (a);
	return (a * (a > b && a < 0) + b * (b >= a && b < 0));
}

double	ft_min_pos(double a, double b)
{
	if (a < 0 && b < 0)
		return (-1);
	if (a < 0)
		return (b);
	if (b < 0)
		return (a);
	return (a * (a < b) + b * (b <= a));
}
