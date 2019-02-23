/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:27:09 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/08 14:44:30 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if ((int)d <= (int)s)
		ft_memcpy(dst, src, len);
	else
	{
		d = dst + len - 1;
		s = src + len - 1;
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}
