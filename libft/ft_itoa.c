/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:02:58 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 11:04:12 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		ft_itoa_rev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	if (str[0] == '-')
		i = 1;
	else
		i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

static void		ft_itoa_fill(char *str, long nb, int i)
{
	while (nb > 0)
	{
		str[i++] = nb % 10 + '0';
		nb /= 10;
	}
	str[i] = '\0';
}

char			*ft_itoa(int n)
{
	char	*ans;
	char	*ret;
	int		i;
	long	nb;

	if (!(ans = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	i = 0;
	nb = n;
	if (nb < 0)
	{
		ans[i++] = '-';
		nb *= -1;
	}
	else if (n == 0)
	{
		ans[i++] = '0';
		ans[i++] = '\0';
	}
	ft_itoa_fill(ans, nb, i);
	ft_itoa_rev(ans);
	if (!(ret = (char *)malloc(sizeof(char) * ft_strlen(ans) + 1)))
		return (NULL);
	ft_strcpy(ret, ans);
	return (ret);
}
