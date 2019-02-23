/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_psigned_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 12:27:48 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/18 19:44:25 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_pputllnbr(intmax_t n)
{
	char	c;
	int		cpt;

	cpt = 0;
	if (n > 9 || n < -9)
		cpt += ft_pputllnbr(n / 10);
	if (n > 0)
		c = n % 10 + '0';
	else
		c = -1 * (n % 10) + '0';
	return (cpt += buffin(c));
}

static void		wololo(intmax_t *nb, t_flags *tflags)
{
	if (tflags->conv == '0')
		*nb = (int)*nb;
	else if (tflags->conv == 'm')
		*nb = (char)*nb;
	else if (tflags->conv == 'h')
		*nb = (short)*nb;
	else if (tflags->conv == 'l')
		*nb = (long int)*nb;
	else if (tflags->conv == 'z')
		*nb = (size_t)*nb;
	else if (tflags->conv == 't')
		*nb = (ptrdiff_t) * nb;
	else if (tflags->conv != 'n')
		*nb = (long long int)*nb;
	else if (tflags->conv != 'j')
		*nb = (intmax_t)*nb;
}

static int		calcul_size(t_flags *tflags, intmax_t nb)
{
	int size;
	int nbsize;
	int tmp;

	tmp = nb;
	nbsize = 1;
	while ((nb /= 10) != 0)
		++nbsize;
	size = ft_max(nbsize, tflags->prec);
	if (tmp == 0 && tflags->prec == 0)
		size = 0;
	if (tmp != 0)
		tflags->prec -= nbsize;
	if (tflags->flags[2] || tflags->flags[3] || tmp < 0)
		++size;
	return (size);
}

int				signed_decimal(va_list list, t_flags *tflags)
{
	intmax_t	nbr;
	int			cpt;
	int			size;

	if (tflags->flags[1] && tflags->prec >= 0)
		tflags->flags[1] = 0;
	cpt = 0;
	nbr = va_arg(list, intmax_t);
	if (tflags->type == 'D')
		tflags->conv = 'l';
	wololo(&nbr, tflags);
	size = calcul_size(tflags, nbr);
	cpt += left_space_padding(tflags, size);
	cpt += left_zero_sign(tflags, nbr, size);
	if (!(tflags->prec == 0 && nbr == 0))
		cpt += (ft_pputllnbr(nbr));
	cpt += right_space_padding(tflags, size);
	return (cpt);
}
