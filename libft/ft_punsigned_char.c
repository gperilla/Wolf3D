/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punsigned_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 14:56:30 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/19 14:17:25 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ccalcul_size(int32_t c)
{
	int size;

	if (c < 128)
		size = 1;
	else if (c < 2048)
		size = 2;
	else if (c < 65536)
		size = 3;
	else
		size = 4;
	return (size);
}

int			unsigned_char(va_list list, t_flags *tflags)
{
	int32_t c;
	int		size;

	size = 1;
	c = va_arg(list, int32_t);
	if (tflags->conv == 'l')
		tflags->type = 'C';
	if (tflags->type == 'c')
		c = (char)c;
	size = ccalcul_size(c);
	if (!tflags->flags[0])
		while (++size <= tflags->min_width)
		{
			if (tflags->flags[1])
				buffin('0');
			else
				buffin(' ');
		}
	print_widechar(c);
	if (tflags->flags[0])
		while (++size <= tflags->min_width)
			buffin(' ');
	--size;
	return (size);
}

int			cstring(t_flags *tflags, char *str)
{
	int i;

	i = -1;
	if (tflags->prec >= 0)
		while (++i < tflags->prec && str[i])
			print_widechar(str[i]);
	else
		while (str[++i])
			print_widechar(str[i]);
	return (i);
}

int			wstring(t_flags *tflags, wchar_t *str)
{
	int i;
	int cpt;

	cpt = 0;
	str = (wchar_t*)str;
	tflags->conv = '0';
	i = -1;
	if (tflags->prec >= 0)
	{
		while (tflags->prec > 0 && str[++i])
			if ((tflags->prec -= ccalcul_size(str[i])) >= 0)
				cpt += print_widechar(str[i]);
	}
	else
		while (str[++i])
			cpt += print_widechar(str[i]);
	return (cpt);
}
