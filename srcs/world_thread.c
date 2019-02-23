/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:37:32 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:30:28 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_world_thread(t_env *env, int x)
{
	env->cam.camx = 2.0 * x / WINX - 1;
	env->ray.dir.x = env->cam.dir.x + env->cam.plane.x * env->cam.camx;
	env->ray.dir.y = env->cam.dir.y + env->cam.plane.y * env->cam.camx;
	env->map.x = (int)env->cam.pos.x;
	env->map.y = (int)env->cam.pos.y;
	env->ray.dlt_dst.x = fabs(1 / env->ray.dir.x);
	env->ray.dlt_dst.y = fabs(1 / env->ray.dir.y);
	env->ray.quart = 0;
	env->ray.org_dir.x = env->ray.dir.x;
	env->ray.org_dir.y = env->ray.dir.y;
	env->hit = 0;
	env->pdst[0] = 9999;
	env->pdst[1] = 9999;
	env->zbuffer[x] = env->wall.dst;
}

void	world_wall(t_env *env, int x)
{
	env->portal[0].height = 0;
	env->portal[1].height = 0;
	world_step_calc(env);
	world_wall_dist(env, x);
	world_wall_init_draw(env);
	world_wall_texture_calc(env);
	world_wall_texture_drawing(env, x);
}

void	world_floor(t_env *env, int x)
{
	world_floor_drawing(env, x);
}

void	world_sky(t_env *env, int x)
{
	world_sky_drawing(env, x);
}

void	*world_thread(void *arg)
{
	t_env	*env;
	int		x;

	env = arg;
	x = env->thrd_nfo.startx;
	while (++x < env->thrd_nfo.endx + 1)
	{
		init_world_thread(env, x);
		world_wall(env, x);
		world_floor(env, x);
		world_sky(env, x);
		portal_coloring(env, x);
		if (!env->zbuffer[x])
			env->zbuffer[x] = env->wall.dst;
	}
	return (NULL);
}
