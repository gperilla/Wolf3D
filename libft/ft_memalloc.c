/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:17:11 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 10:43:21 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*ans;
	size_t	i;

	if (!(ans = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		ans[i++] = 0;
	return (ans);
}
