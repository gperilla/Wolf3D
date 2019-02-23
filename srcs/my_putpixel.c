/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_putpixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:21:01 by gperilla          #+#    #+#             */
/*   Updated: 2018/05/21 00:40:43 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	my_putpixel(t_env *env, int x, int y, int color)
{
	int		pos;
	int8_t	mask;

	if ((x >= 0 && x < WINX) && (y >= 0 && y < WINY))
	{
		pos = (y * env->mlx.s_l + x * (env->mlx.bpp / 8));
		mask = color;
		env->mlx.pix[pos] = mask;
		color = color >> 8;
		mask = color;
		env->mlx.pix[pos + 1] = mask;
		color = color >> 8;
		mask = color;
		env->mlx.pix[pos + 2] = mask;
		color = color >> 8;
		mask = color;
		env->mlx.pix[pos + 3] = mask;
	}
}
