/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_through_portal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:22:11 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:28:26 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_through_portal_p(t_env *env, int p)
{
	init_move_through(env, p);
	if ((env->portal[p].card % 2 == 0 && env->portal[p].card
		== env->portal[(p + 1) % 2].card - 1) || (env->portal[p].card % 2 == 1
			&& env->portal[p].card == env->portal[(p + 1) % 2].card + 1))
		move_through_same_dir(env);
	else if (env->portal[p].card == env->portal[(p + 1) % 2].card)
		move_through_opposite_dir(env, p);
	else if ((env->portal[p].card == 0 && env->portal[(p + 1) % 2].card == 2)
			|| (env->portal[p].card == 1 && env->portal[(p + 1) % 2].card == 3)
			|| (env->portal[p].card == 2 && env->portal[(p + 1) % 2].card == 1)
			|| (env->portal[p].card == 3 && env->portal[(p + 1) % 2].card == 0))
		move_through_one_quarter(env, p);
	else if ((env->portal[p].card == 0 && env->portal[(p + 1) % 2].card == 3)
			|| (env->portal[p].card == 1 && env->portal[(p + 1) % 2].card == 2)
			|| (env->portal[p].card == 2 && env->portal[(p + 1) % 2].card == 0)
			|| (env->portal[p].card == 3 && env->portal[(p + 1) % 2].card == 1))
		move_through_other_quarter(env, p);
}

void	move_through_portal(t_env *env)
{
	int p;

	p = -1;
	while (++p < 2)
	{
		if (env->pdst[p] != 0)
			continue;
		if ((int)fmod(env->movep.oldx + env->cam.dir.x * (env->mov_spd *
			(env->cam.sprint + 1)), env->wmap.height) == env->portal[p].pos.x
			&& (int)fmod(env->movep.oldy + env->cam.dir.y * (env->mov_spd
				* (env->cam.sprint + 1)), env->wmap.width)
				== env->portal[p].pos.y)
		{
			move_through_portal_p(env, p);
			if (env->cheatbreak == 1)
				break ;
		}
	}
}
