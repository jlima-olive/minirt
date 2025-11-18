/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:07:18 by jlima-so          #+#    #+#             */
/*   Updated: 2025/11/18 16:28:22 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_libft.h"

void	ft_striteri(char const *s, void (*f)(unsigned int, char *))
{
	int		ind;
	char	*str;

	if (s != NULL && f != NULL)
	{
		str = (char *)s;
		ind = -1;
		while (str[++ind])
			f(ind, str + ind);
	}
}
