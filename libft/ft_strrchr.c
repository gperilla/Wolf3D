/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:56:56 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/08 15:34:48 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int ans;

	i = 0;
	ans = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
			ans = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char*)s + i);
	if (ans >= 0)
		return ((char*)s + ans);
	return (NULL);
}
