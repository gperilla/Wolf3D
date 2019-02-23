/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:35:29 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:35:53 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_straight(t_env *env)
{
	if (env->cam.mov == 1 || env->autorun)
	{
		move_through_portal(env);
		if (env->wmap.val[((int)(env->movep.oldx + env->cam.dir.x *
			(env->mov_spd * (env->cam.sprint + 1)))) % env->wmap.height]
			[(int)env->movep.oldy] <= 0)
			env->cam.pos.x += env->cam.dir.x * env->mov_spd
			/ (env->cam.crouch + 1) * (env->cam.sprint + 1);
		if (env->wmap.val[(int)(env->movep.oldx)][((int)(env->movep.oldy +
			env->cam.dir.y * (env->mov_spd * (env->cam.sprint + 1))))
			% env->wmap.width] <= 0)
			env->cam.pos.y += env->cam.dir.y * env->mov_spd / (env->cam.crouch
				+ 1) * (env->cam.sprint + 1);
	}
	else if (env->cam.mov == -1)
	{
		if (env->wmap.val[((int)(env->movep.oldx - env->cam.dir.x *
			env->mov_spd)) % env->wmap.height][(int)env->movep.oldy] <= 0)
			env->cam.pos.x -= env->cam.dir.x * env->mov_spd / 3;
		if (env->wmap.val[(int)(env->movep.oldx)][((int)(env->movep.oldy -
			env->cam.dir.y * env->mov_spd)) % env->wmap.width] <= 0)
			env->cam.pos.y -= env->cam.dir.y * env->mov_spd / 3;
	}
}

void	strafe(t_env *env)
{
	if (env->cam.straf == 1)
	{
		if (env->wmap.val[((int)(env->movep.oldx + env->cam.plane.x *
			env->mov_spd)) % env->wmap.height][(int)env->movep.oldy] <= 0)
			env->cam.pos.x += env->cam.plane.x * env->mov_spd;
		if (env->wmap.val[(int)(env->movep.oldx)][((int)(env->movep.oldy +
			env->cam.plane.y * env->mov_spd)) % env->wmap.width] <= 0)
			env->cam.pos.y += env->cam.plane.y * env->mov_spd;
	}
	else if (env->cam.straf == -1)
	{
		if (env->wmap.val[((int)(env->movep.oldx - env->cam.plane.x *
			env->mov_spd)) % env->wmap.height][(int)env->movep.oldy] <= 0)
			env->cam.pos.x -= env->cam.plane.x * env->mov_spd;
		if (env->wmap.val[(int)(env->movep.oldx)][((int)(env->movep.oldy -
			env->cam.plane.y * env->mov_spd)) % env->wmap.width] <= 0)
			env->cam.pos.y -= env->cam.plane.y * env->mov_spd;
	}
}
