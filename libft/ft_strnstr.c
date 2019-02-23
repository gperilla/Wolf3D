/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:24:23 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/10 00:39:42 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;
	int j;

	len++;
	if (needle[0] == '\0')
		return ((char*)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && len--)
	{
		if (haystack[i] == needle[j])
		{
			while (needle[j] && haystack[i + j] == needle[j] && len--)
				j++;
			if (needle[j] == '\0')
				return ((char*)haystack + i);
			len += (size_t)j;
			j = 0;
		}
		i++;
	}
	return (NULL);
}
