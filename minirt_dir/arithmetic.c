/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namejojo <namejojo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 11:35:51 by namejojo          #+#    #+#             */
/*   Updated: 2025/10/10 13:37:38 by namejojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_point	add(t_point one, t_point two)
{
	t_point ret;

	ret.x = one.x + two.x;
	ret.y = one.y + two.y;
	ret.z = one.z + two.z;
	return (ret);
}

t_point	sub(t_point one, t_point two)
{
	t_point ret;

	ret.x = one.x - two.x;
	ret.y = one.y - two.y;
	ret.z = one.z - two.z;
	return (ret);
}

t_point	mult_class(t_point point, float a)
{
	t_point	ret;

	ret.x = point.x * a;
	ret.y = point.y * a;
	ret.z = point.z * a;
	return (ret);
}

int	equal(t_point one, t_point two)
{
	return ((one.x == two.x) && (one.y == two.y) && (one.z == two.z));
}
