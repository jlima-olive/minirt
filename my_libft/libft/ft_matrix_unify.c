/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_unify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:36:54 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:28:22 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft.h"

void	ft_matrix_uni(char **dest, char **src)
{
	int	ind;

	if (src == NULL || dest == NULL)
		return ;
	ind = -1;
	while (src[++ind])
		dest[ind] = src[ind];
	dest[ind] = NULL;
}
