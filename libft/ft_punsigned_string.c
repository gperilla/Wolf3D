/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punsigned_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:39:57 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/22 11:10:38 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_strllen(wchar_t *s, t_flags *tflags)
{
	int i;
	int cpt;

	i = -1;
	cpt = 0;
	while (s[++i] != '\0')
	{
		if (s[i] < 128 && (tflags->prec < 0 || cpt + 1 <= tflags->prec))
			++cpt;
		else if (s[i] < 2048 && (tflags->prec < 0 || cpt + 2 <= tflags->prec))
			cpt += 2;
		else if (s[i] < 65536 && (tflags->prec < 0 || cpt + 3 <= tflags->prec))
			cpt += 3;
		else if (tflags->prec < 0 || cpt + 4 <= tflags->prec)
			cpt += 4;
		else
			break ;
	}
	return (cpt);
}

static int		str_wrt(t_flags *tflags, int size, char *str, wchar_t *wstr)
{
	int i;
	int cpt;

	cpt = 0;
	i = size;
	if (!tflags->flags[0])
		while (++i <= tflags->min_width)
		{
			if (tflags->flags[1])
				cpt += buffin('0');
			else
				cpt += buffin(' ');
		}
	if (tflags->type == 'S')
		cpt += wstring(tflags, wstr);
	else
		cpt += cstring(tflags, str);
	if (tflags->flags[0])
		while (++i <= tflags->min_width)
			cpt += buffin(' ');
	return (cpt);
}

int				unsigned_string(va_list list, t_flags *tflags)
{
	int		size;
	char	*str;
	wchar_t *wstr;

	str = NULL;
	wstr = NULL;
	if ((size = get_normed(tflags, list, &str, &wstr)) == 6)
		return (size);
	if (size)
	{
		if (tflags->type == 's')
			size = ft_strlen(str);
		else
			size = ft_strllen(wstr, tflags);
		if (tflags->prec >= 0)
			size = ft_min(size, tflags->prec);
	}
	return (str_wrt(tflags, size, str, wstr));
}
