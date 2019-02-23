/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbuffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:04:23 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/19 12:21:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		buffin(char c)
{
	int			i;
	static char	*buff;

	if (!(buff))
	{
		if (!(buff = malloc(sizeof(char) * BUFF_PSIZE + 1)))
			exit(-1);
		ft_bzero(buff, BUFF_PSIZE + 1);
	}
	i = ft_strlen(buff);
	if (c != -1)
		buff[i] = c;
	if (i == BUFF_PSIZE - 1 || c == '\n' || c == '\0' || c == -1)
		flush_buff(&buff);
	if (c == '\0')
		write(1, "\0", 1);
	return (1);
}

void	flush_buff(char **buff)
{
	int ret;

	ret = write(1, *buff, ft_strlen(*buff));
	ft_bzero(*buff, BUFF_PSIZE);
}
