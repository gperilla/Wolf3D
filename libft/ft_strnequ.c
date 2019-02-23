/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:14:26 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 10:54:51 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && n--)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
