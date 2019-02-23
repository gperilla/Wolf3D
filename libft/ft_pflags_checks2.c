/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pflags_checks2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:06:33 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/22 10:52:41 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_flags(char c, t_flags *tflags)
{
	char	*sflg;
	int		i;

	if (!(sflg = ft_strdup("-0+ #")))
		return (0);
	i = -1;
	while (sflg[++i])
		if (c == sflg[i])
		{
			if (c != '0')
			{
				tflags->period = 0;
				tflags->flags[i] = 1;
			}
			else if (!tflags->period)
				tflags->flags[i] = 1;
		}
	free(sflg);
	if (c == '.')
	{
		tflags->prec = 0;
		tflags->period = 1;
	}
	return (1);
}

int		check_conv(char c, t_flags *tflags)
{
	char	*scnv;
	int		i;

	if (!(scnv = ft_strdup("hlLqjzt")))
		return (-1);
	i = -1;
	while (++i < 7)
		if (c == scnv[i])
		{
			tflags->period = 0;
			if (c == 'h' && tflags->conv == 'h')
				tflags->conv = 'm';
			else if (c == 'l' && tflags->conv == 'l')
				tflags->conv = 'n';
			else if (c == 'h' && tflags->conv == '0')
				tflags->conv = c;
			else if (c != 'h')
				tflags->conv = c;
			free(scnv);
			return (1);
		}
	free(scnv);
	return (1);
}

int		check_type(char c, t_flags *tflags)
{
	char	*styp;
	int		i;

	if (!(styp = ft_strdup("dDioOxXbBuUfFeEgGaAcCsSpnm%")))
		return (-1);
	i = -1;
	while (styp[++i] != '\0')
		if (c == styp[i])
		{
			tflags->type = styp[i];
			free(styp);
			return (1);
		}
	free(styp);
	return (0);
}

int		check_inexisant(char c, t_flags *tflags)
{
	char	*str;
	int		ret;
	int		i;

	i = -1;
	ret = 0;
	str = ft_strdup("*. +#-0123456789hlLqjztdDioOxXbBuUfFeEgGaAcCsSpnm%");
	while (str[++i])
		if (c == str[i])
			ret = 1;
	free(str);
	if (ret == 0)
	{
		tflags->type = c;
		tflags->inexist = 1;
	}
	return (ret);
}
