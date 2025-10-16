/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deg_n_rad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:02:04 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/16 17:04:28 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

float	ft_deg_to_rad(float	deg)
{
	return (deg * PI / 180.0);
}

float	ft_rad_to_deg(float	rad)
{
	return (rad / 180.0 * PI);
}
