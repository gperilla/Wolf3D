/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:49:52 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:37:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		my_key_release(int key, t_env *env)
{
	if (key == 13 || key == 126 || key == 1 || key == 125)
		env->cam.mov = 0;
	else if (key == 0 || key == 2)
		env->cam.straf = 0;
	else if (key == 12 || key == 14 || key == KEY_LEFT || key == KEY_RIGHT)
		env->cam.rot = 0;
	else if (key == 256)
		env->cam.crouch = 0;
	else if (key == 257)
		env->cam.sprint = 0;
	else if (key == KEY_SHIFT_RIGHT && env->cam.zoom)
	{
		env->cam.zoom = 0;
		env->cam.dir.x /= 2;
		env->cam.dir.y /= 2;
	}
	else if (key == 49 && !env->pause)
		env->cam.jmp = -1;
	game_loop(env);
	return (0);
}

int		my_pointer_motion(int x, int y, t_env *env)
{
	env->rot_spd = ROT_SPD * abs(x - env->mousex) / 4;
	if (x > env->mousex)
		env->cam.rot = 1;
	else if (x < env->mousex)
		env->cam.rot = -1;
	env->mousex = x;
	if (!env->pause)
		env->cam.vview = (WINY / 2 - y) / 2;
	game_loop(env);
	env->cam.rot = 0;
	env->rot_spd = ROT_SPD;
	return (0);
}

int		my_button_press(int button, int x, int y, t_env *env)
{
	if (env->pause && button == MOUSE_LEFT)
	{
		if (x >= WINX / 2 - env->mlx.cont.wdth / 2 && x <= WINX / 2 +
			env->mlx.cont.wdth / 2
		&& y >= 2 * WINY / 5 && y <= 2 * WINY / 5 + env->mlx.cont.hght)
			env->pause = 0;
		else if (x >= WINX / 2 - env->mlx.quit.wdth / 2 && x <= WINX / 2 +
			env->mlx.quit.wdth / 2
		&& y >= 3 * WINY / 5 && y <= 3 * WINY / 5 + env->mlx.quit.hght)
			clean_exit(env);
	}
	return (0);
}

int		my_destroy_notify(void)
{
	clean_exit(NULL);
	return (0);
}
