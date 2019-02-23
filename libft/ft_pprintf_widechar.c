/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pprintf_widechar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:16:42 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/18 16:28:41 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_wd1(int32_t c)
{
	c = (char)c;
	buffin(c);
	return (1);
}

static int		print_wd2(int32_t c)
{
	unsigned char tmp[2];

	tmp[1] = c % 64;
	tmp[1] += 0x80;
	c = c >> 6;
	tmp[0] = c;
	tmp[0] += 0xC0;
	buffin(tmp[0]);
	buffin(tmp[1]);
	return (2);
}

static int		print_wd3(int32_t c)
{
	unsigned char tmp[3];

	tmp[2] = c % 64;
	tmp[2] += 0x80;
	c = c >> 6;
	tmp[1] = c % 64;
	tmp[1] += 0x80;
	c = c >> 6;
	tmp[0] = c;
	tmp[0] += 0xE0;
	buffin(tmp[0]);
	buffin(tmp[1]);
	buffin(tmp[2]);
	return (3);
}

static int		print_wd4(int32_t c)
{
	unsigned char tmp[4];

	tmp[3] = c % 64;
	tmp[3] += 0x80;
	c = c >> 6;
	tmp[2] = c % 64;
	tmp[2] += 0x80;
	c = c >> 6;
	tmp[1] = c % 64;
	tmp[1] += 0x80;
	c = c >> 6;
	tmp[0] = c;
	tmp[0] += 0xF0;
	buffin(tmp[0]);
	buffin(tmp[1]);
	buffin(tmp[2]);
	buffin(tmp[3]);
	return (4);
}

int				print_widechar(int32_t c)
{
	if (c < 128)
		return (print_wd1(c));
	else if (c < 2048)
		return (print_wd2(c));
	else if (c < 65536)
		return (print_wd3(c));
	else
		return (print_wd4(c));
}
