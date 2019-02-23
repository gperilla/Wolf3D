/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:32:32 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:17:26 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		choose_block(int x, int y)
{
	if (x < WINY / 20 && y < WINY - WINY / 20)
		return (1);
	else if (x >= WINY / 20 && y < WINY - WINY / 20)
		return (2);
	else if (x < WINY / 20 && y >= WINY - WINY / 20)
		return (3);
	else
		return (4);
}

void	draw_block(t_env *env)
{
	int x;
	int y;
	int color;
	int t;

	t = env->block;
	x = -1;
	while (++x < WINY / 10)
	{
		y = WINY - WINY / 10 - 1;
		while (++y < WINY)
		{
			if (env->block > 8)
				t = choose_block(x, y);
			color = my_get_pixel_color_tex(env->tex[t], (int)((float)x /
				(WINY / 10) * env->tex[t].wdth), (int)((float)(y - (WINY - WINY
				/ 10)) / (WINY / 10) * env->tex[t].hght));
			my_putpixel(env, x, y, color);
		}
	}
}

void	multithreading(t_env *env)
{
	int		i;
	t_env	arg[NB_THRD];

	i = -1;
	while (++i < NB_THRD)
	{
		env->thrd_nfo.num = i;
		env->thrd_nfo.startx = WINX / NB_THRD * i;
		env->thrd_nfo.endx = WINX / NB_THRD * (i + 1);
		memcpy(&arg[i], env, sizeof(t_env));
		pthread_create(&env->thrd_id[i], NULL, world_thread, &arg[i]);
	}
	i = -1;
	while (++i < NB_THRD)
	{
		pthread_join(env->thrd_id[i], NULL);
	}
}

void	game_paused(t_env *env)
{
	int x;
	int y;

	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
			my_putpixel(env, x, y,
				bandw_color(my_get_pixel_color_env(env, x, y)));
	}
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.img, 0, 0);
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.cont.img,
		WINX / 2 - env->mlx.cont.wdth / 2, 2 * WINY / 5);
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.quit.img,
		WINX / 2 - env->mlx.quit.wdth / 2, 3 * WINY / 5);
}

int		game_loop(t_env *env)
{
	init_img(env);
	if (end_game(env))
		return (0);
	env->movep.oldx = env->cam.pos.x;
	env->movep.oldy = env->cam.pos.y;
	if (!env->pause)
	{
		move_straight(env);
		strafe(env);
		rotations(env);
		walk_through_map(env);
		crouch_and_jump(env);
	}
	world_sky_init(env);
	multithreading(env);
	draw_crosshair(env);
	draw_block(env);
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.img, 0, 0);
	if (env->pause)
		game_paused(env);
	return (0);
}
