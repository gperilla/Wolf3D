/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_portal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:26:52 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:07:45 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_shoot_portal(t_env *env, int i)
{
	Mix_PlayChannel(-1, env->sound.effect[i], 0);
	env->ray.dir.x = env->cam.dir.x;
	env->ray.dir.y = env->cam.dir.y;
	env->map.x = (int)env->cam.pos.x;
	env->map.y = (int)env->cam.pos.y;
	env->ray.dlt_dst.x = fabs(1 / env->ray.dir.x);
	env->ray.dlt_dst.y = fabs(1 / env->ray.dir.y);
	env->hit = 0;
	world_step_calc(env);
}

void	init_portal_travelling(t_env *env, float *nbx, float *nby)
{
	env->hit = 0;
	if (env->ray.sd_dst.x < env->ray.sd_dst.y)
	{
		env->ray.sd_dst.x += env->ray.dlt_dst.x;
		env->map.x += env->step.x;
		env->side = 0;
		nbx += env->step.x;
	}
	else
	{
		env->ray.sd_dst.y += env->ray.dlt_dst.y;
		env->map.y += env->step.y;
		env->side = 1;
		nby += env->step.y;
	}
}

void	shoot_portal_through_map(t_env *env)
{
	if (env->map.x < 0 || env->map.x > env->wmap.height - 1 || env->map.y < 0
		|| env->map.y > env->wmap.width - 1)
	{
		if (env->map.x < 0)
		{
			env->map.x += env->wmap.height;
		}
		else if (env->map.x > env->wmap.height - 1)
		{
			env->map.x -= env->wmap.height;
		}
		if (env->map.y < 0)
		{
			env->map.y += env->wmap.width;
		}
		else if (env->map.y > env->wmap.width - 1)
		{
			env->map.y -= env->wmap.width;
		}
	}
}

void	search_portal_hit(t_env *env, float *nbx, float *nby)
{
	while (!env->hit)
	{
		init_portal_travelling(env, nbx, nby);
		shoot_portal_through_map(env);
		if (*nby >= 750 || *nbx >= 750)
			env->hit = -1;
		if (env->wmap.val[env->map.x][env->map.y] != 0 && !env->hit)
			env->hit = 1;
	}
}
