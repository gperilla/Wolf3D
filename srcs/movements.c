/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:24:00 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:35:50 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	one_rotation(t_env *env, float *oldrx, float *oldplx)
{
	*oldrx = env->cam.dir.x;
	env->cam.dir.x = env->cam.dir.x * cos(-env->rot_spd) - env->cam.dir.y *
	sin(-env->rot_spd);
	env->cam.dir.y = *oldrx * sin(-env->rot_spd) + env->cam.dir.y *
	cos(-env->rot_spd);
	*oldplx = env->cam.plane.x;
	env->cam.plane.x = env->cam.plane.x * cos(-env->rot_spd) -
	env->cam.plane.y * sin(-env->rot_spd);
	env->cam.plane.y = *oldplx * sin(-env->rot_spd) + env->cam.plane.y *
	cos(-env->rot_spd);
}

void	rotations(t_env *env)
{
	float oldrx;
	float oldplx;

	if (env->cam.rot == 1)
		one_rotation(env, &oldrx, &oldplx);
	else if (env->cam.rot == -1)
	{
		oldrx = env->cam.dir.x;
		env->cam.dir.x = env->cam.dir.x * cos(env->rot_spd) - env->cam.dir.y *
		sin(env->rot_spd);
		env->cam.dir.y = oldrx * sin(env->rot_spd) + env->cam.dir.y *
		cos(env->rot_spd);
		oldplx = env->cam.plane.x;
		env->cam.plane.x = env->cam.plane.x * cos(env->rot_spd) -
		env->cam.plane.y * sin(env->rot_spd);
		env->cam.plane.y = oldplx * sin(env->rot_spd) + env->cam.plane.y *
		cos(env->rot_spd);
	}
}

void	walk_through_in_a_sens(t_env *env)
{
	if (env->cam.pos.x < 0)
	{
		if (env->wmap.val[env->wmap.height - 1][(int)env->cam.pos.y] == 0)
			env->cam.pos.x += env->wmap.height;
		else
			env->cam.pos.x = 0 + MARGE;
	}
	else if (env->cam.pos.x >= env->wmap.height)
	{
		if (env->wmap.val[0][(int)env->cam.pos.y] == 0)
			env->cam.pos.x -= env->wmap.height;
		else
			env->cam.pos.x = env->wmap.height - MARGE;
	}
}

void	walk_through_map(t_env *env)
{
	walk_through_in_a_sens(env);
	if (env->cam.pos.y < 0)
	{
		if (env->wmap.val[(int)env->cam.pos.x][env->wmap.width - 1] == 0)
			env->cam.pos.y += env->wmap.width;
		else
			env->cam.pos.y = 0 + MARGE;
	}
	else if (env->cam.pos.y >= env->wmap.width)
	{
		if (env->wmap.val[(int)env->cam.pos.x][0] == 0)
			env->cam.pos.y -= env->wmap.width;
		else
			env->cam.pos.y = env->wmap.width - MARGE;
	}
}

void	crouch_and_jump(t_env *env)
{
	if (env->cam.crouch)
		if (env->cam.crch_val < 10)
			env->cam.crch_val += 2;
	if (!env->cam.crouch)
		if (env->cam.crch_val > 0)
			env->cam.crch_val -= 2;
	if (env->cam.jmp == 1)
	{
		if (env->cam.jmp_val < 100)
			env->cam.jmp_val += (100 - env->cam.jmp_val) / 3 + 1;
	}
	else if (env->cam.jmp == -1)
	{
		if (env->cam.jmp_val > 0)
			env->cam.jmp_val -= 17;
		if (env->cam.jmp_val <= 0)
		{
			env->cam.jmp_val = 0;
			env->cam.jmp = 0;
		}
	}
}
