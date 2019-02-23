/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_punsigned_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 18:18:29 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/18 20:13:12 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	wololo(uintmax_t *nb, t_flags *tflags)
{
	if (tflags->conv == '0')
		*nb = (unsigned int)*nb;
	else if (tflags->conv == 'm')
		*nb = (unsigned char)*nb;
	else if (tflags->conv == 'h')
		*nb = (unsigned short)*nb;
	else if (tflags->conv == 'l')
		*nb = (unsigned long int)*nb;
	else if (tflags->conv == 'z')
		*nb = (size_t)*nb;
	else if (tflags->conv == 't')
		*nb = (ptrdiff_t) * nb;
	else if (tflags->conv != 'n')
		*nb = (unsigned long long int)*nb;
	else if (tflags->conv != 'j')
		*nb = (uintmax_t)*nb;
	if (tflags->type == 'p' && tflags->min_width > 0)
		tflags->min_width -= 2;
}

static int	ucalcul_size(t_flags *tflags, uintmax_t nb, char *base)
{
	int size;
	int nbsize;
	int sizeb;
	int tmp;

	sizeb = ft_strlen(base);
	size = 1;
	tmp = nb;
	nbsize = 1;
	while ((nb /= sizeb) != 0)
		++nbsize;
	size = ft_max(nbsize, tflags->prec);
	if (nb == 0 && tflags->prec == 0)
		size = 0;
	if (tmp != 0)
		tflags->prec -= nbsize;
	if (tflags->flags[4] && (tmp != 0 || tflags->type == 'p'))
	{
		if (tflags->type == 'x' || tflags->type == 'X' || tflags->type == 'p')
			size += 2;
		else if (tflags->type == 'o' || tflags->type == 'O')
			size += 1;
	}
	return (size);
}

static char	*get_base(t_flags *tflags)
{
	char *base;

	if (tflags->type == 'b' || tflags->type == 'B')
		base = ft_strdup("01");
	else if (tflags->type == 'o' || tflags->type == 'O')
		base = ft_strdup("01234567");
	else if (tflags->type == 'u' || tflags->type == 'U')
		base = ft_strdup("0123456789");
	else if (tflags->type == 'x' || tflags->type == 'p')
		base = ft_strdup("0123456789abcdef");
	else
		base = ft_strdup("0123456789ABCDEF");
	return (base);
}

static int	prefixe_writing(t_flags *tflags, uintmax_t nbr)
{
	int cpt;

	cpt = 0;
	if (tflags->flags[4] || tflags->type == 'p')
	{
		if ((tflags->type == 'x' && nbr != 0) || tflags->type == 'p')
		{
			buffin('0');
			buffin('x');
			cpt = 2;
		}
		else if (tflags->type == 'X' && nbr != 0)
		{
			buffin('0');
			buffin('X');
			cpt = 2;
		}
		else if ((tflags->type == 'o' || tflags->type == 'O' || tflags->type
		== 'b' || tflags->type == 'B') && (nbr != 0 || tflags->prec == 0))
		{
			buffin('0');
			cpt = 1;
		}
	}
	return (cpt);
}

int			unsigned_int(va_list list, t_flags *tflags)
{
	int			cpt;
	int			size;
	int			size_pref;
	uintmax_t	nbr;
	char		*base;

	cpt = 0;
	nbr = va_arg(list, uintmax_t);
	if (tflags->type == 'U' || tflags->type == 'O' || tflags->type == 'p')
		tflags->conv = 'l';
	wololo(&nbr, tflags);
	base = get_base(tflags);
	size = ucalcul_size(tflags, nbr, base);
	size_pref = 0;
	cpt += uleft_space_padding(tflags, size);
	cpt += prefixe_writing(tflags, nbr);
	cpt += uleft_zero_sign(tflags, size, nbr);
	if (!(tflags->prec == 0 && nbr == 0))
		cpt += ft_pprint_base(nbr, base);
	else if (tflags->min_width > 0)
		buffin(' ');
	cpt += uright_space_padding(tflags, size);
	free(base);
	return (cpt);
}
