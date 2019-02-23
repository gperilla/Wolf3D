/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 10:20:53 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/18 16:32:40 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		inexistant_flag(t_flags *tflags)
{
	int cpt;

	cpt = 0;
	if (!tflags->flags[0])
		while (++cpt < tflags->min_width)
		{
			if (tflags->flags[1])
				buffin('0');
			else
				buffin(' ');
		}
	buffin(tflags->type);
	if (tflags->flags[0])
		while (++cpt < tflags->min_width)
			buffin(' ');
	return (cpt);
}

int		percent(t_flags *tflags)
{
	int cpt;

	cpt = 1;
	if (tflags->min_width > 1 && !tflags->flags[0])
		while (--tflags->min_width)
		{
			if (tflags->flags[1])
				buffin('0');
			else
				buffin(' ');
			++cpt;
		}
	buffin('%');
	if (tflags->min_width > 1 && tflags->flags[0])
		while (--tflags->min_width)
		{
			buffin(' ');
			++cpt;
		}
	return (cpt);
}

int		missdirection(va_list list, t_flags *tflags)
{
	if (tflags->inexist)
		return (inexistant_flag(tflags));
	if (tflags->type == 'd' || tflags->type == 'i' || tflags->type == 'D')
		return (signed_decimal(list, tflags));
	else if (tflags->type == 'c' || tflags->type == 'C')
		return (unsigned_char(list, tflags));
	else if (tflags->type == 's' || tflags->type == 'S')
		return (unsigned_string(list, tflags));
	else if (tflags->type == 'o' || tflags->type == 'O' || tflags->type == 'u'
		|| tflags->type == 'U' || tflags->type == 'x' || tflags->type == 'X'
		|| tflags->type == 'b' || tflags->type == 'B' || tflags->type == 'p')
		return (unsigned_int(list, tflags));
	else
		return (percent(tflags));
	return (1);
}
