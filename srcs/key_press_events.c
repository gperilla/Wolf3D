/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:46:09 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:21:23 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	my_key_press1(int key, t_env *env)
{
	static int i;

	if (key == 13 || key == 126)
		env->cam.mov = 1;
	else if (key == 1 || key == 125)
		env->cam.mov = -1;
	else if (key == 0)
		env->cam.straf = -1;
	else if (key == 2)
		env->cam.straf = 1;
	else if (key == 14 || key == KEY_RIGHT)
		env->cam.rot = 1;
	else if (key == 12 || key == KEY_LEFT)
		env->cam.rot = -1;
	else if (key == 256)
		env->cam.crouch = 1;
	else if (key == 49 && env->cam.jmp == 0 && !env->pause)
	{
		env->cam.jmp = 1;
		i = (i + 1) % 2;
		Mix_PlayChannel(9, env->sound.effect[i + 5], 0);
	}
}

void	my_key_press2(int key, t_env *env)
{
	if (key == 35)
		env->pause = (++env->pause % 2);
	else if (key == 257)
		env->cam.sprint = 1;
	else if (key == KEY_SHIFT_RIGHT && !env->cam.zoom)
	{
		env->cam.zoom = 1;
		env->cam.dir.x *= 2;
		env->cam.dir.y *= 2;
	}
	else if (key == KEY_R && !env->pause)
		env->autorun = (env->autorun + 1) % 2;
	else if (key == KEY_N)
		shoot_portal(env, 0);
	else if (key == KEY_M)
		shoot_portal(env, 1);
	else if (key == KEY_X)
		shoot_portal(env, -1);
	else if (key == KEY_C)
		shoot_portal(env, -2);
}

void	my_key_press3(int key, t_env *env)
{
	if (key == KEY_1)
		env->block = 1;
	else if (key == KEY_2)
		env->block = 2;
	else if (key == KEY_3)
		env->block = 3;
	else if (key == KEY_4)
		env->block = 4;
	else if (key == KEY_5)
		env->block = 5;
	else if (key == KEY_6)
		env->block = 6;
	else if (key == KEY_7)
		env->block = 7;
	else if (key == KEY_8)
		env->block = 8;
	else if (key == KEY_9)
		env->block = 9;
	else if (key == KEY_O)
		quick_save(env);
	else if (key == KEY_I)
		load_map(env, "saves/qsave");
}

int		my_key_press(int key, t_env *env)
{
	if (key == 53)
		clean_exit(env);
	if (env->over)
		return (0);
	my_key_press1(key, env);
	my_key_press2(key, env);
	my_key_press3(key, env);
	game_loop(env);
	return (0);
}
