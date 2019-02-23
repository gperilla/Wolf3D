/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:07:03 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/22 10:53:18 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *tflags)
{
	int i;

	i = -1;
	while (++i < 5)
		tflags->flags[i] = 0;
	tflags->min_width = 0;
	tflags->period = 0;
	tflags->prec = -1;
	tflags->conv = '0';
	tflags->type = '0';
	tflags->inexist = 0;
}

int		get_flags(const char *str, va_list list, t_flags *tflags)
{
	int j;

	j = -1;
	while (str[++j] != '\0')
	{
		if (!(check_flags(str[j], tflags)))
			return (j - 1);
		if (!(check_width(str[j], tflags, list)))
			return (j - 1);
		if (!(check_conv(str[j], tflags)))
			return (j - 1);
		if (check_type(str[j], tflags))
			return (j);
		if (!check_inexisant(str[j], tflags))
			return (j);
	}
	return (j - 1);
}

void	check_width_star(t_flags *tflags, va_list list)
{
	if (tflags->period == 0 || tflags->period == 2)
	{
		tflags->min_width = va_arg(list, int);
		if (tflags->min_width < 0)
		{
			tflags->flags[0] = 1;
			tflags->min_width *= -1;
		}
	}
	else if (tflags->period == 1)
	{
		tflags->prec = ft_max(va_arg(list, int), -1);
	}
}

int		check_width(char c, t_flags *tflags, va_list list)
{
	if (ft_isdigit(c))
	{
		if (c != '0' && tflags->period == 0)
		{
			tflags->min_width = 0;
			tflags->min_width = tflags->min_width * 10 + c - '0';
			tflags->period = 2;
		}
		else if (tflags->period == 1)
			tflags->prec = tflags->prec * 10 + c - '0';
		else if (tflags->period == 2)
			tflags->min_width = tflags->min_width * 10 + c - '0';
	}
	if (c == '*')
		check_width_star(tflags, list);
	return (1);
}
