/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:18:16 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:17:45 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		my_get_pixel_color_tex(t_texture tex, int x, int y)
{
	int	pos;
	int color;

	pos = y * tex.s_l + x * tex.bpp / 8;
	color = ((unsigned char)tex.pix[pos] << 0)
		| ((unsigned char)tex.pix[pos + 1] << 8)
		| ((unsigned char)tex.pix[pos + 2] << 16)
		| ((unsigned char)tex.pix[pos + 3] << 24);
	return (color);
}

int		my_get_pixel_color_env(t_env *env, int x, int y)
{
	int	pos;
	int color;

	pos = y * env->mlx.s_l + x * env->mlx.bpp / 8;
	color = ((unsigned char)env->mlx.pix[pos] << 0)
		| ((unsigned char)env->mlx.pix[pos + 1] << 8)
		| ((unsigned char)env->mlx.pix[pos + 2] << 16)
		| ((unsigned char)env->mlx.pix[pos + 3] << 24);
	return (color);
}
