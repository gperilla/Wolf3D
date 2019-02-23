/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:27:28 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:27:53 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	calc_wall_tex_y(t_env *env, int d)
{
	env->wall.tex.y = ((d * (env->tex[env->wall.texnum].hght - 1)) /
	env->wall.height) / 256;
	if (env->wall.tex.y < 0)
		env->wall.tex.y = 0;
	else if (env->wall.tex.y >= env->tex[env->wall.texnum].hght)
		env->wall.tex.y = env->tex[env->wall.texnum].hght - 1;
}

void	world_wall_texture_drawing(t_env *env, int x)
{
	int				y;
	int				d;
	unsigned int	color;
	unsigned int	c1;

	y = env->wall.start - 1;
	while (++y < env->wall.end)
	{
		c1 = my_get_pixel_color_env(env, x, y);
		if (c1 != 0 && (c1 >> 24) == 0)
			continue;
		d = (y - env->wall.d_y) * 256 - WINY * 128 + env->wall.height * 128;
		calc_wall_tex_y(env, d);
		color = my_get_pixel_color_tex(env->tex[env->wall.texnum],
			env->wall.tex.x, env->wall.tex.y);
		if (env->side)
			color = ((color >> 1) & 0xFF7F7F7F);
		if (c1 == 0)
			my_putpixel(env, x, y, color);
		else
		{
			color = color_interpolate(c1, color, (c1 >> 24) / 255.0);
			my_putpixel(env, x, y, color);
		}
	}
}
