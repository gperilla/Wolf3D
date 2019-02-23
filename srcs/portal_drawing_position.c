/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_drawing_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:24:15 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:48:45 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	calcul_portal_height_not_side(t_env *env, float *tmpx)
{
	if (!env->ray.quart)
	{
		if (env->ray.dir.x > 0)
			(*tmpx) -= (env->cam.pos.x - (int)env->cam.pos.x);
		else
			(*tmpx) += (env->cam.pos.x - (int)env->cam.pos.x) - 1;
	}
	else
	{
		if (env->ray.org_dir.y > 0)
			(*tmpx) -= (env->cam.pos.y - (int)env->cam.pos.y);
		else
			(*tmpx) += (env->cam.pos.y - (int)env->cam.pos.y) - 1;
	}
	env->wall.dst = (*tmpx) / fabs(env->ray.dir.x);
}

void	calcul_portal_height_side(t_env *env, float *tmpy)
{
	if (!env->ray.quart)
	{
		if (env->ray.dir.y > 0)
			(*tmpy) -= (env->cam.pos.y - (int)env->cam.pos.y);
		else
			(*tmpy) += (env->cam.pos.y - (int)env->cam.pos.y) - 1;
	}
	else
	{
		if (env->ray.org_dir.x > 0)
			(*tmpy) -= (env->cam.pos.x - (int)env->cam.pos.x);
		else
			(*tmpy) += (env->cam.pos.x - (int)env->cam.pos.x) - 1;
	}
	env->wall.dst = (*tmpy) / fabs(env->ray.dir.y);
}

void	apply_height_to_portal(t_env *env, int p)
{
	if (env->cam.crch_val > 0)
		env->portal[p].d_y -= (WINY / 5) * (env->cam.crch_val /
			(10.0 * env->wall.dst));
	if (env->cam.jmp_val > 0)
		env->portal[p].d_y += (WINY / 3) * (env->cam.jmp_val /
			(100.0 * env->wall.dst));
	env->portal[p].d_y += (env->cam.vview);
	if (!env->side && !env->ray.quart)
		env->portal[p].wallx = env->cam.pos.y + env->wall.dst * env->ray.dir.y;
	else if (!env->side && env->ray.quart)
		env->portal[p].wallx = env->cam.pos.x + env->wall.dst *
		env->ray.org_dir.x;
	else if (env->side && !env->ray.quart)
		env->portal[p].wallx = env->cam.pos.x + env->wall.dst * env->ray.dir.x;
	else
		env->portal[p].wallx = env->cam.pos.y + env->wall.dst *
		env->ray.org_dir.y;
	env->portal[p].wallx -= floor(env->portal[p].wallx);
}

void	calcul_portal_height(t_env *env, int x, int nbx, int nby)
{
	float tmpx;
	float tmpy;

	tmpx = nbx;
	tmpy = nby;
	env->portal[env->cheatp].side = env->side;
	if (!env->side)
		calcul_portal_height_not_side(env, &tmpx);
	else
		calcul_portal_height_side(env, &tmpy);
	env->zbuffer[x] = env->wall.dst;
	if (env->wall.dst < env->pdst[env->cheatp])
		env->pdst[env->cheatp] = env->wall.dst;
	env->portal[env->cheatp].height = (int)(WINY / env->wall.dst);
	env->portal[env->cheatp].d_y = 0;
}
