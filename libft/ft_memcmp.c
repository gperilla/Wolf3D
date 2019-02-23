/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:26:54 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/09 17:32:21 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*d1;
	const char	*d2;
	int			i;

	d1 = s1;
	d2 = s2;
	i = 0;
	while (n--)
	{
		if (d1[i] != d2[i])
			return ((unsigned char)(d1[i]) - (unsigned char)(d2[i]));
		i++;
	}
	return (0);
}
