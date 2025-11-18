/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:00:28 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/18 16:28:22 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft.h"

char	*ft_mat_join(char **mat, int indv, int ind, int total)
{
	char	*ret;

	if (mat == NULL)
		return (NULL);
	while (mat[indv])
	{
		ind = 0;
		while (mat[indv][ind])
			ind++;
		total += ind + 1;
		indv++;
	}
	ret = ft_calloc(1, total);
	ind = 0;
	indv = -1;
	while (ret && mat[++indv])
	{
		while (mat[indv])
		{
			ret[ind] = *(mat[indv]);
			ind++;
			(mat[indv])++;
		}
	}
	return (ret);
}
