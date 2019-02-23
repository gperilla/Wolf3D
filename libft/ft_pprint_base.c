/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:10:06 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/19 18:24:05 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_pprint_base(uintmax_t n, const char *base)
{
	int		cpt;
	int		tmp;
	int		sizeb;
	char	c;

	sizeb = ft_strlen(base);
	if (sizeb < 2)
		return (-1);
	cpt = 0;
	if (n > (uintmax_t)sizeb - 1)
		cpt += ft_pprint_base(n / sizeb, base);
	tmp = n % sizeb;
	c = base[tmp];
	buffin(c);
	++cpt;
	return (cpt);
}

int		uleft_space_padding(t_flags *tflags, int size)
{
	int cpt;
	int i;

	cpt = 0;
	i = size;
	if ((tflags->flags[3] || tflags->flags[2]) && tflags->prec < 0
	&& size < tflags->min_width)
	{
		cpt += buffin(' ');
		--tflags->min_width;
	}
	if (!tflags->flags[0] && (!tflags->flags[1] || tflags->prec >= 0))
	{
		while (i <= --tflags->min_width)
			cpt += buffin(' ');
		++tflags->min_width;
	}
	return (cpt);
}

int		uleft_zero_sign(t_flags *tflags, int size, uintmax_t nbr)
{
	int i;
	int cpt;

	cpt = 0;
	if ((nbr == 0 && tflags->prec > 0) || (tflags->type == 'o'
		&& tflags->prec >= 0 && nbr > 0 && tflags->flags[4]))
		--tflags->prec;
	if ((tflags->flags[1] && !tflags->flags[0]) || (tflags->prec > 0))
	{
		if (!tflags->flags[0])
			i = ft_max(tflags->min_width - size, tflags->prec);
		else
			i = tflags->prec;
		while (i-- > 0)
		{
			cpt += buffin('0');
		}
	}
	return (cpt);
}

int		uright_space_padding(t_flags *tflags, int size)
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
