/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_travelling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:34:25 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:25:59 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	world_step_calc(t_env *env)
{
	if (env->ray.dir.x < 0)
	{
		env->step.x = -1;
		env->ray.sd_dst.x = (env->cam.pos.x - env->map.x) * env->ray.dlt_dst.x;
	}
	else
	{
		env->step.x = 1;
		env->ray.sd_dst.x = (env->map.x + 1.0 - env->cam.pos.x)
			* env->ray.dlt_dst.x;
	}
	if (env->ray.dir.y < 0)
	{
		env->step.y = -1;
		env->ray.sd_dst.y = (env->cam.pos.y - env->map.y) * env->ray.dlt_dst.y;
	}
	else
	{
		env->step.y = 1;
		env->ray.sd_dst.y = (env->map.y + 1.0 - env->cam.pos.y)
			* env->ray.dlt_dst.y;
	}
}

void	loop_the_map(t_env *env, int nbx, int nby)
{
	if (env->map.x < 0 || env->map.x > env->wmap.height - 1 || env->map.y < 0
		|| env->map.y > env->wmap.width - 1)
	{
		if (env->map.x < 0)
			env->map.x += env->wmap.height;
		else if (env->map.x > env->wmap.height - 1)
			env->map.x -= env->wmap.height;
		if (env->map.y < 0)
			env->map.y += env->wmap.width;
		else if (env->map.y > env->wmap.width - 1)
			env->map.y -= env->wmap.width;
	}
	if (nby >= 750 || nbx >= 750)
		env->hit = 1;
	if (env->wmap.val[env->map.x][env->map.y] != 0 && !env->hit)
		env->hit = 1;
}

void	handle_one_side(t_env *env, float *nbx)
{
	if (!env->ray.quart)
	{
		if (env->ray.dir.x > 0)
			*nbx -= (env->cam.pos.x - (int)env->cam.pos.x);
		else
			*nbx += (env->cam.pos.x - (int)env->cam.pos.x) - 1;
	}
	else
	{
		if (env->ray.org_dir.y > 0)
			*nbx -= (env->cam.pos.y - (int)env->cam.pos.y);
		else
			*nbx += (env->cam.pos.y - (int)env->cam.pos.y) - 1;
	}
	env->wall.dst = *nbx / fabs(env->ray.dir.x);
}

void	handle_sides(t_env *env, float *nbx, float *nby)
{
	if (!env->side)
		handle_one_side(env, nbx);
	else
	{
		if (!env->ray.quart)
		{
			if (env->ray.dir.y > 0)
				*nby -= (env->cam.pos.y - (int)env->cam.pos.y);
			else
				*nby += (env->cam.pos.y - (int)env->cam.pos.y) - 1;
		}
		else
		{
			if (env->ray.org_dir.x > 0)
				*nby -= (env->cam.pos.x - (int)env->cam.pos.x);
			else
				*nby += (env->cam.pos.x - (int)env->cam.pos.x) - 1;
		}
		env->wall.dst = *nby / fabs(env->ray.dir.y);
	}
}

void	move_a_step(t_env *env, float *nbx, float *nby)
{
	env->hit = 0;
	if (env->ray.sd_dst.x < env->ray.sd_dst.y)
	{
		env->ray.sd_dst.x += env->ray.dlt_dst.x;
		env->map.x += env->step.x;
		env->side = 0;
		*nbx += abs(env->step.x);
	}
	else
	{
		env->ray.sd_dst.y += env->ray.dlt_dst.y;
		env->map.y += env->step.y;
		env->side = 1;
		*nby += abs(env->step.y);
	}
}
