/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:36:27 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:07:59 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	world_sky_init(t_env *env)
{
	env->sky.start = 0;
	env->sky.dir = (float)env->cam.dir.x;
	if (env->cam.zoom)
		env->sky.dir /= 2;
	if (env->sky.dir == 1.0)
		env->sky.start = 3830;
	else if (env->cam.dir.y < 0)
	{
		env->sky.start = ((float)acos(env->sky.dir) / 2 * M_PI)
			* (env->sky.texture.wdth / 2);
	}
	else
	{
		env->sky.start = (env->sky.texture.wdth / 2);
		env->sky.start += (1 - ((float)acos(env->sky.dir) / 2 * M_PI))
			* (env->sky.texture.wdth / 2);
	}
}

void	world_sky_drawing(t_env *env, int x)
{
	int y;
	int color;
	int tmp;

	y = -1;
	while (++y < WINY - 1)
	{
		color = my_get_pixel_color_env(env, x, y);
		if ((color & 0xFF000000) == 0 && y >= env->wall.start)
			continue;
		tmp = (x / 2 + env->sky.start) % (env->sky.texture.wdth - 1);
		if (!color)
			color = my_get_pixel_color_tex(env->sky.texture, tmp + 1,
				(y + 2 * env->sky.texture.hght - env->cam.vview)
					% (env->sky.texture.hght - 1) + 1);
		else if ((color & 0xFF000000) != 0)
			color = color_interpolate(color,
				my_get_pixel_color_tex(env->sky.texture, tmp + 1,
					(y + (2 * env->sky.texture.hght) - env->cam.vview)
						% env->sky.texture.hght),
						(((color & 0xFF000000) >> 24) / 255.0));
		my_putpixel(env, x, y, color);
	}
}
