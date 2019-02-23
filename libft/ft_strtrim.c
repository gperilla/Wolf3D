/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:09:34 by gperilla          #+#    #+#             */
/*   Updated: 2018/03/28 15:28:27 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	char	*ans;
	int		i;

	if (s == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	ft_strcpy(str, &s[i]);
	i = 0;
	while (str[i])
		i++;
	--i;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') && i != 0)
		str[i--] = '\0';
	if (!(ans = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	ft_strcpy(ans, str);
	free(str);
	return (ans);
}
