/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_drawing2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:10:31 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:05:22 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_right(t_env *env, float *right, int p)
{
	*right = (((env->portalc.y - env->portalc.y0)
	* (env->portalc.y - env->portalc.y0))
	/ ((float)env->portal[p].height / 2.2 * env->portal[p].height / 2.2));
}

void	portal_coloring_circle(t_env *env, int x, int p)
{
	float left;
	float right;

	left = (((x - env->portalc.x0) * (x - env->portalc.x0))
	/ ((float)env->portal[p].height / 3 * env->portal[p].height / 3));
	while (++env->portalc.y < env->portalc.end)
	{
		init_right(env, &right, p);
		if (left + right >= 1 && left + right <= 1.1)
		{
			env->portalc.key = 255 - (int)((left + right - 1) / 0.1 * 255);
			if (env->portalc.key > 255)
				env->portalc.key = 0;
			if (my_get_pixel_color_env(env, x, env->portalc.y) == 0)
				my_putpixel(env, x, env->portalc.y, ((env->portalc.key << 24)
				| env->portal[p].filter));
		}
		else if (left + right > 1.1)
		{
			env->portalc.c1 = my_get_pixel_color_env(env, x, env->portalc.y);
			if (env->portalc.c1 != 0 && (env->portalc.c1 >> 24) == 0)
				continue;
			outside_portal_circle(env, x, p);
		}
	}
}

void	portal_coloring(t_env *env, int x)
{
	int p;

	p = -1;
	while (++p < 2)
	{
		if (env->portal[p].height)
		{
			init_portal_coloring(env, x, p);
			portal_coloring_circle(env, x, p);
		}
	}
}
