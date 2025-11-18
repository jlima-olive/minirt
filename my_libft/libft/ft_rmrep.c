/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmrep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 09:45:14 by namejojo          #+#    #+#             */
/*   Updated: 2025/11/18 16:28:22 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft.h"

char	*ft_rmrep(char *str, char rep)
{
	int	ind;

	if (str == NULL || *str == '\0')
		return (str);
	ind = 1;
	while (str[ind])
	{
		if (str[ind] == rep && str[ind - 1] == rep)
			ft_memmove(str + ind - 1, str + ind, ft_strlen(str + ind) + 1);
		else
			ind++;
	}
	return (str);
}
