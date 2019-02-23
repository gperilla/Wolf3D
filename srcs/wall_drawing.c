/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:31:54 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:27:48 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	pass_through_portal(t_env *env, int x, float *nbx, float *nby)
{
	if ((env->portal[env->cheatp].card == 0 && !env->side &&
		env->step.x > 0) || (env->portal[env->cheatp].card == 1 &&
			!env->side && env->step.x < 0)
	|| (env->portal[env->cheatp].card == 2 && env->side &&
		env->step.y < 0) || (env->portal[env->cheatp].card == 3 &&
			env->side && env->step.y > 0))
	{
		view_through_portal(env, x, nbx, nby);
		++env->loop;
		if (env->loop < 500)
			env->hit = -1;
	}
}

void	world_wall_dist(t_env *env, int x)
{
	float	nbx;
	float	nby;

	nbx = 0;
	nby = 0;
	env->loop = 0;
	while (env->hit <= 0)
	{
		move_a_step(env, &nbx, &nby);
		env->cheatp = -1;
		while (++env->cheatp < 2)
		{
			if (env->map.x == env->portal[env->cheatp].pos.x && env->map.y ==
				env->portal[env->cheatp].pos.y)
				pass_through_portal(env, x, &nbx, &nby);
		}
		loop_the_map(env, nbx, nby);
	}
	handle_sides(env, &nbx, &nby);
}

void	world_wall_init_draw(t_env *env)
{
	env->wall.height = (int)(WINY / env->wall.dst);
	env->wall.start = -env->wall.height / 2 + WINY / 2;
	env->wall.end = env->wall.height / 2 + WINY / 2;
	env->wall.d_y = 0;
	if (env->cam.crch_val > 0)
		env->wall.d_y -= (WINY / 5) * (env->cam.crch_val /
			(10.0 * env->wall.dst));
	if (env->cam.jmp_val > 0)
		env->wall.d_y += (WINY / 3) * (env->cam.jmp_val /
			(100.0 * env->wall.dst));
	env->wall.d_y += (env->cam.vview);
	env->wall.start += env->wall.d_y;
	env->wall.end += env->wall.d_y;
	if (env->wall.start < 0 || env->wall.start > WINY)
		env->wall.start = 0;
	if (env->wall.end > WINY || env->wall.end < 0)
		env->wall.end = WINY;
}

void	texture_calc_side(t_env *env)
{
	if (!env->ray.quart)
	{
		if (!env->side && env->ray.dir.x > 0)
			env->wall.tex.x = env->tex[env->wall.texnum].wdth -
			env->wall.tex.x - 1;
		if (env->side && env->ray.dir.y < 0)
			env->wall.tex.x = env->tex[env->wall.texnum].wdth -
			env->wall.tex.x - 1;
	}
	else
	{
		if (!env->side && env->ray.org_dir.y < 0)
			env->wall.tex.x = env->tex[env->wall.texnum].wdth -
			env->wall.tex.x - 1;
		if (env->side && env->ray.org_dir.x > 0)
			env->wall.tex.x = env->tex[env->wall.texnum].wdth -
			env->wall.tex.x - 1;
	}
	if (env->wall.tex.x < 0)
		env->wall.tex.x = 0;
	else if (env->wall.tex.x >= env->tex[env->wall.texnum].wdth)
		env->wall.tex.x = env->tex[env->wall.texnum].wdth - 1;
}

void	world_wall_texture_calc(t_env *env)
{
	env->wall.texnum = abs(env->wmap.val[env->map.x][env->map.y]) % 100;
	if (env->wall.texnum > 8)
	{
		if (env->side && env->step.y < 0)
			env->wall.texnum = 1;
		else if (env->side && env->step.y > 0)
			env->wall.texnum = 2;
		else if (!env->side && env->step.x < 0)
			env->wall.texnum = 3;
		else
			env->wall.texnum = 4;
	}
	if (!env->side && !env->ray.quart)
		env->wall.wallx = env->cam.pos.y + env->wall.dst * env->ray.dir.y;
	else if (!env->side && env->ray.quart)
		env->wall.wallx = env->cam.pos.x + env->wall.dst * env->ray.org_dir.x;
	else if (env->side && !env->ray.quart)
		env->wall.wallx = env->cam.pos.x + env->wall.dst * env->ray.dir.x;
	else
		env->wall.wallx = env->cam.pos.y + env->wall.dst * env->ray.org_dir.y;
	env->wall.wallx -= floor(env->wall.wallx);
	env->wall.tex.x = (int)(env->wall.wallx * env->tex[env->wall.texnum].wdth);
	texture_calc_side(env);
}
