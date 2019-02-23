/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pflags_usage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:14:40 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/18 16:26:52 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			left_space_padding(t_flags *tflags, int size)
{
	int cpt;
	int i;

	cpt = 0;
	i = size;
	if (!tflags->flags[0] && (!tflags->flags[1] || tflags->prec >= 0))
	{
		while (i <= --tflags->min_width)
			cpt += buffin(' ');
		++tflags->min_width;
	}
	return (cpt);
}

static int	zero_filling(t_flags *tflags, int size)
{
	int cpt;
	int i;

	cpt = 0;
	if ((tflags->flags[1] && !tflags->flags[0]) || (tflags->prec > 0))
	{
		if (!tflags->flags[0])
			i = ft_max(tflags->min_width - size, tflags->prec);
		else
			i = tflags->prec;
		while (i-- > 0)
		{
			buffin('0');
			++cpt;
		}
	}
	return (cpt);
}

int			left_zero_sign(t_flags *tflags, intmax_t nbr, int size)
{
	int cpt;
	int sign;

	sign = 0;
	cpt = 0;
	if (tflags->flags[3] && !tflags->flags[2] && nbr >= 0)
		cpt += buffin(' ');
	if (tflags->flags[2] || nbr < 0)
	{
		sign = 1;
		if (nbr < 0)
			buffin('-');
		else if (tflags->flags[2])
			buffin('+');
		++cpt;
	}
	if (nbr == 0 && tflags->prec > 0)
		--tflags->prec;
	cpt += zero_filling(tflags, size);
	return (cpt);
}

int			right_space_padding(t_flags *tflags, int size)
{
	int cpt;
	int i;

	cpt = 0;
	if (tflags->flags[0])
	{
		i = size;
		while (i < tflags->min_width)
		{
			cpt += buffin(' ');
			++i;
		}
	}
	return (cpt);
}
