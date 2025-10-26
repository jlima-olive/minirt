/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deg_n_rad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:02:04 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/26 18:48:13 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

double	ft_deg_to_rad(double	deg)
{
	return (deg * (PI / 180.0));
}

double	ft_rad_to_deg(double	rad)
{
	return (rad / 180.0 * PI);
}
