/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:35:34 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:10:21 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	world_floor_drawing(t_env *env, int x)
{
	int				y;
	unsigned int	color;
	unsigned int	c1;

	y = env->wall.end - 1;
	while (++y < WINY)
	{
		c1 = my_get_pixel_color_env(env, x, y);
		if (c1 != 0 && (c1 >> 24) == 0)
			continue;
		if ((x + y) % 2 == 0)
			color = 0x707070;
		else
			color = 0x909090;
		if (c1 == 0)
			my_putpixel(env, x, y, color);
		else
		{
			color = color_interpolate(c1, color, (c1 >> 24) / 255.0);
			my_putpixel(env, x, y, color);
		}
	}
}
