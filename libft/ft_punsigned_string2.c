/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punsigned_string2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:54:53 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/22 11:10:42 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	buffin_null(void)
{
	buffin('(');
	buffin('n');
	buffin('u');
	buffin('l');
	buffin('l');
	buffin(')');
	return (6);
}

int			get_normed(t_flags *tf, va_list lst, char **str, wchar_t **wstr)
{
	int size;

	size = 1;
	if (tf->conv == 'l')
		tf->type = 'S';
	if (tf->type == 's')
		if (!(*str = va_arg(lst, char*)))
		{
			if (tf->prec != 0)
				return (buffin_null());
			else
				size = 0;
		}
	if (tf->type == 'S')
		if (!(*wstr = va_arg(lst, wchar_t*)))
		{
			if (tf->prec != 0)
				return (buffin_null());
			else
				size = 0;
		}
	return (size);
}
