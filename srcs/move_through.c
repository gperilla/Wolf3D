/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_through.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:19:36 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:29:10 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_move_through(t_env *env, int p)
{
	env->movep.dx = env->cam.pos.x - (int)env->cam.pos.x;
	env->movep.dy = env->cam.pos.y - (int)env->cam.pos.y;
	env->cam.pos.x = env->portal[(p + 1) % 2].pos.x;
	env->cam.pos.y = env->portal[(p + 1) % 2].pos.y;
	env->cheatbreak = 0;
}

void	move_through_same_dir(t_env *env)
{
	env->cam.pos.x += env->movep.dx;
	env->cam.pos.y += env->movep.dy;
	env->movep.oldx = env->cam.pos.x;
	env->movep.oldy = env->cam.pos.y;
	env->cheatbreak = 1;
}

void	move_through_opposite_dir(t_env *env, int p)
{
	env->cam.dir.x = -env->cam.dir.x;
	env->cam.dir.y = -env->cam.dir.y;
	env->cam.plane.x = -env->cam.plane.x;
	env->cam.plane.y = -env->cam.plane.y;
	if (env->portal[p].card < 2)
	{
		env->cam.pos.x += ft_sign(env->cam.dir.x);
		env->cam.pos.x += env->movep.dx;
		env->cam.pos.y += 1 - env->movep.dy;
	}
	else
	{
		env->cam.pos.y += ft_sign(env->cam.dir.y);
		env->cam.pos.y += env->movep.dy;
		env->cam.pos.x += 1 - env->movep.dx;
	}
	env->movep.oldx = env->cam.pos.x;
	env->movep.oldy = env->cam.pos.y;
	env->cheatbreak = 1;
}

void	move_through_one_quarter(t_env *env, int p)
{
	float oldrx;
	float oldplx;

	oldrx = env->cam.dir.x;
	env->cam.dir.x = env->cam.dir.x * cos(M_PI / 2) - env->cam.dir.y
	* sin(M_PI / 2);
	env->cam.dir.y = oldrx * sin(M_PI / 2) + env->cam.dir.y * cos(M_PI / 2);
	oldplx = env->cam.plane.x;
	env->cam.plane.x = env->cam.plane.x * cos(M_PI / 2) - env->cam.plane.y
	* sin(M_PI / 2);
	env->cam.plane.y = oldplx * sin(M_PI / 2) + env->cam.plane.y
	* cos(M_PI / 2);
	if (env->portal[p].card < 2)
		env->cam.pos.y += ft_sign(env->cam.dir.y);
	else
		env->cam.pos.x += ft_sign(env->cam.dir.x);
	env->cam.pos.x += 1 - env->movep.dy;
	env->cam.pos.y += 1 - env->movep.dx;
	env->movep.oldx = env->cam.pos.x;
	env->movep.oldy = env->cam.pos.y;
	env->cheatbreak = 1;
}

void	move_through_other_quarter(t_env *env, int p)
{
	float oldrx;
	float oldplx;

	oldrx = env->cam.dir.x;
	env->cam.dir.x = env->cam.dir.x * cos(-M_PI / 2) - env->cam.dir.y
	* sin(-M_PI / 2);
	env->cam.dir.y = oldrx * sin(-M_PI / 2) + env->cam.dir.y * cos(-M_PI / 2);
	oldplx = env->cam.plane.x;
	env->cam.plane.x = env->cam.plane.x * cos(-M_PI / 2) - env->cam.plane.y
	* sin(-M_PI / 2);
	env->cam.plane.y = oldplx * sin(-M_PI / 2) + env->cam.plane.y
	* cos(-M_PI / 2);
	if (env->portal[p].card < 2)
		env->cam.pos.y += ft_sign(env->cam.dir.y);
	else
		env->cam.pos.x += ft_sign(env->cam.dir.x);
	env->cam.pos.x += 1 - env->movep.dy;
	env->cam.pos.y += 1 - env->movep.dx;
	env->movep.oldx = env->cam.pos.x;
	env->movep.oldy = env->cam.pos.y;
	env->cheatbreak = 1;
}
