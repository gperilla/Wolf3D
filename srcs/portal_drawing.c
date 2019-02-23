/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_drawing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:21:43 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 14:59:49 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_portal_coloring_side(t_env *env, int p)
{
	if (!env->portal[p].side && env->ray.dir.x > 0)
		env->wall.tex.x = env->tex[env->wall.texnum].wdth - env->wall.tex.x - 1;
	if (env->portal[p].side && env->ray.dir.y < 0)
		env->wall.tex.x = env->tex[env->wall.texnum].wdth - env->wall.tex.x - 1;
	if (env->wall.tex.x < 0)
		env->wall.tex.x = 0;
	else if (env->wall.tex.x >= env->tex[env->wall.texnum].wdth)
		env->wall.tex.x = env->tex[env->wall.texnum].wdth - 1;
}

void	multiple_faces(t_env *env, int p)
{
	if (env->portal[p].side && env->ray.org_dir.y < 0)
		env->wall.texnum = 1;
	else if (env->portal[p].side && env->ray.org_dir.y > 0)
		env->wall.texnum = 2;
	else if (!env->portal[p].side && env->ray.org_dir.x < 0)
		env->wall.texnum = 3;
	else
		env->wall.texnum = 4;
}

void	init_portal_coloring(t_env *env, int x, int p)
{
	env->portalc.y0 = WINY / 2 + env->portal[p].d_y;
	env->portalc.x0 = (int)(x + (0.5 - env->portal[p].wallx)
	* env->portal[p].height);
	env->portalc.y = WINY / 2 - env->portal[p].height / 2 + env->portal[p].d_y;
	if (env->portalc.y < 0)
		env->portalc.y = 0;
	env->portalc.end = WINY / 2 + env->portal[p].height / 2
	+ env->portal[p].d_y;
	if (env->portalc.end > WINY - 1)
		env->portalc.end = WINY - 1;
	env->wall.texnum =
		abs(env->wmap.val[env->portal[p].pos.x][env->portal[p].pos.y]) % 100;
	if (env->wall.texnum > 8)
	{
		multiple_faces(env, p);
	}
	env->wall.tex.x = (int)(env->portal[p].wallx
		* env->tex[env->wall.texnum].wdth);
	init_portal_coloring_side(env, p);
}

void	interpolate_color(t_env *env, int x)
{
	env->portalc.color = color_interpolate(env->portalc.c1,
		env->portalc.color, (env->portalc.c1 >> 24) / 255.0);
	my_putpixel(env, x, env->portalc.y, env->portalc.color);
}

void	outside_portal_circle(t_env *env, int x, int p)
{
	int d;

	d = (env->portalc.y - env->portal[p].d_y) * 256 - WINY * 128
	+ env->portal[p].height * 128;
	env->wall.tex.y = ((d * (env->tex[env->wall.texnum].hght - 1))
	/ env->portal[p].height) / 256;
	if (env->wall.tex.y < 0)
		env->wall.tex.y = 0;
	else if (env->wall.tex.y >= env->tex[env->wall.texnum].hght)
		env->wall.tex.y = env->tex[env->wall.texnum].hght - 1;
	env->portalc.color = my_get_pixel_color_tex(env->tex[env->wall.texnum],
		env->wall.tex.x, env->wall.tex.y);
	if (env->portal[p].side)
		env->portalc.color = ((env->portalc.color >> 1) & 0xFF7F7F7F);
	if (env->portalc.c1 == 0)
		my_putpixel(env, x, env->portalc.y, env->portalc.color);
	else
		interpolate_color(env, x);
}
