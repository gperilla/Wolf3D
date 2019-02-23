/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 16:11:48 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/21 21:28:25 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	main_while(const char *format, va_list list, t_flags *tflags)
{
	int i;
	int j;
	int cpt;

	cpt = 0;
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] != '\%')
		{
			buffin(format[i]);
			++cpt;
		}
		else
		{
			j = get_flags(format + ++i, list, tflags);
			i += j;
			if (tflags->type != '0')
				cpt += missdirection(list, tflags);
			init_flags(tflags);
		}
	}
	return (cpt);
}

int			ft_printf(const char *format, ...)
{
	va_list	list;
	t_flags	*tflags;
	int		cpt;

	if (!(tflags = malloc(sizeof(t_flags))))
		return (-1);
	if (!(tflags->flags = malloc(sizeof(uint8_t) * 6)))
		return (-1);
	init_flags(tflags);
	va_start(list, format);
	cpt = main_while(format, list, tflags);
	buffin(-1);
	va_end(list);
	free(tflags->flags);
	free(tflags);
	return (cpt);
}
