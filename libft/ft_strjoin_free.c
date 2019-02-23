/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 22:33:59 by gperilla          #+#    #+#             */
/*   Updated: 2017/12/08 15:36:19 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, size_t n)
{
	int		i;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(tab = ft_strjoin((const char*)s1, (const char*)s2)))
		return (NULL);
	if (n == 1)
		free(s1);
	if (n == 2)
		free(s2);
	if (n == 3)
	{
		free(s2);
		free(s1);
	}
	return (tab);
}
