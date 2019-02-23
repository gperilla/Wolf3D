/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_through_portal2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:25:57 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:03:17 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	reverse_direction_portals(t_env *env, int p)
{
	env->step.x = -env->step.x;
	env->step.y = -env->step.y;
	env->map.x = env->portal[(p + 1) % 2].pos.x;
	env->map.y = env->portal[(p + 1) % 2].pos.y;
	if (env->portal[p].card < 2)
		env->map.x += env->step.x;
	else
		env->map.y += env->step.y;
}

void	init_quarter_turn_portals(t_env *env)
{
	float tmp;
	float oldrx;

	env->ray.quart = (env->ray.quart + 1) % 2;
	oldrx = env->ray.dir.x;
	env->ray.dir.x = env->ray.dir.x * cos(M_PI / 2) - env->ray.dir.y
	* sin(M_PI / 2);
	env->ray.dir.y = oldrx * sin(M_PI / 2) + env->ray.dir.y * cos(M_PI / 2);
	env->ray.dlt_dst.x = fabs(1 / env->ray.dir.x);
	env->ray.dlt_dst.y = fabs(1 / env->ray.dir.y);
	tmp = env->ray.sd_dst.x;
	env->ray.sd_dst.x = env->ray.sd_dst.y;
	env->ray.sd_dst.y = tmp;
}

void	one_quarter_turn_portals(t_env *env, int p, float *nbx, float *nby)
{
	int		ttmp;

	init_quarter_turn_portals(env);
	if (env->ray.dir.y < 0)
		env->step.y = -1;
	else
		env->step.y = 1;
	if (env->ray.dir.x < 0)
		env->step.x = -1;
	else
		env->step.x = 1;
	ttmp = *nbx;
	*nbx = *nby;
	*nby = ttmp;
	env->map.x = env->portal[(p + 1) % 2].pos.x;
	env->map.y = env->portal[(p + 1) % 2].pos.y;
	if (env->portal[p].card < 2)
		env->map.y += env->step.y;
	else
		env->map.x += env->step.x;
}

void	init_other_quarter_turn_portals(t_env *env)
{
	float tmp;
	float oldrx;

	env->ray.quart = (env->ray.quart + 1) % 2;
	oldrx = env->ray.dir.x;
	env->ray.dir.x = env->ray.dir.x * cos(-M_PI / 2) - env->ray.dir.y
	* sin(-M_PI / 2);
	env->ray.dir.y = oldrx * sin(-M_PI / 2) + env->ray.dir.y * cos(-M_PI / 2);
	env->ray.dlt_dst.x = fabs(1 / env->ray.dir.x);
	env->ray.dlt_dst.y = fabs(1 / env->ray.dir.y);
	tmp = env->ray.sd_dst.x;
	env->ray.sd_dst.x = env->ray.sd_dst.y;
	env->ray.sd_dst.y = tmp;
}

void	the_other_quarter_turn(t_env *env, int p, float *nbx, float *nby)
{
	int		ttmp;

	init_other_quarter_turn_portals(env);
	if (env->ray.dir.y < 0)
		env->step.y = -1;
	else
		env->step.y = 1;
	if (env->ray.dir.x < 0)
		env->step.x = -1;
	else
		env->step.x = 1;
	ttmp = *nbx;
	*nbx = *nby;
	*nby = ttmp;
	env->map.x = env->portal[(p + 1) % 2].pos.x;
	env->map.y = env->portal[(p + 1) % 2].pos.y;
	if (env->portal[p].card < 2)
		env->map.y += env->step.y;
	else
		env->map.x += env->step.x;
}
