/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:41:15 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 10:48:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char *s;

	if (!(s = (char *)malloc(sizeof(char) * ft_strlen((char*)str) + 1)))
		return (NULL);
	ft_strcpy(s, str);
	return (s);
}
