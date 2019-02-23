/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:31:35 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 16:58:48 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	create_block(t_env *env)
{
	if (!env->side)
		env->map.x -= env->step.x;
	else
		env->map.y -= env->step.y;
	if (env->map.x < 0)
		env->map.x += env->wmap.height;
	if (env->map.y < 0)
		env->map.y += env->wmap.width;
	if (env->map.x >= env->wmap.height)
		env->map.x -= env->wmap.height;
	if (env->map.y >= env->wmap.width)
		env->map.y -= env->wmap.width;
	if (env->map.x == (int)env->cam.pos.x && env->map.y == (int)env->cam.pos.y)
		env->wmap.val[env->map.x][env->map.y] = -env->block;
	else
		env->wmap.val[env->map.x][env->map.y] = env->block;
}

void	create_portal(t_env *env, int p)
{
	env->portal[p].pos.x = env->map.x;
	env->portal[p].pos.y = env->map.y;
	if (!env->side)
	{
		if (env->step.x > 0)
			env->portal[p].card = 0;
		else
			env->portal[p].card = 1;
	}
	else
	{
		if (env->step.y > 0)
			env->portal[p].card = 3;
		else
			env->portal[p].card = 2;
	}
}

void	shoot_portal(t_env *env, int p)
{
	static int	i;
	float		nbx;
	float		nby;

	nbx = 0;
	nby = 0;
	if (env->pause || env->over)
		return ;
	i = (i + 1) % 5;
	init_shoot_portal(env, i);
	search_portal_hit(env, &nbx, &nby);
	if (env->hit < 0)
		return ;
	if (p == -1)
	{
		env->wmap.val[env->map.x][env->map.y] = 0;
		return ;
	}
	if (p == -2)
	{
		create_block(env);
		return ;
	}
	create_portal(env, p);
}
