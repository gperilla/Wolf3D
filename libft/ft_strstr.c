/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:01:45 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/08 16:53:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	j = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i + j] == needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char*)haystack + i);
			j = 0;
		}
		i++;
	}
	return (NULL);
}
