/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 12:00:29 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 13:05:30 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_point	mult_class(t_point point, float a)
{
	t_point	ret;

	ret.x = point.x * a;
	ret.y = point.y * a;
	ret.z = point.z * a;
	return (ret);
}

t_point	mult_vec(t_point point, float a)
{
	t_point	ret;

	ret.x = point.x * a;
	ret.y = point.y * a;
	ret.z = point.z * a;
	return (ret);
}

t_point	mult_rgb(t_point point, float a)
{
	t_point	ret;

	ret.x = point.x * a;
	ret.y = point.y * a;
	ret.z = point.z * a;
	return (ret);
}
