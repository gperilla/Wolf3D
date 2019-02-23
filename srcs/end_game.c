/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:40:11 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:09:56 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	its_over_anakin(t_env *env, int y, int step)
{
	int x;

	x = -1;
	while (++x < env->end.wdth)
	{
		env->cheatcolor = my_get_pixel_color_tex(env->end, (int)((float)x
		/ env->end.wdth * WINX), (int)((float)y / env->end.hght * WINY));
		env->cheatcolor = color_interpolate(0, env->cheatcolor, step / 52.0);
		my_putpixel(env, x, y, env->cheatcolor);
	}
}

int		is_it_over(t_env *env)
{
	int i;
	int j;

	i = -1;
	while (++i < env->wmap.height)
	{
		j = -1;
		while (++j < env->wmap.width)
		{
			if (env->wmap.val[i][j] != 0)
				return (0);
		}
	}
	return (1);
}

int		end_game(t_env *env)
{
	int			y;
	static int	step;

	if (!env->over)
	{
		if (!is_it_over(env))
			return (0);
		env->over = 1;
		Mix_FreeMusic(env->sound.music);
		env->sound.music = Mix_LoadMUS("data/Yello.wav");
		Mix_PlayMusic(env->sound.music, -1);
	}
	++step;
	y = -1;
	while (++y < env->end.hght)
		its_over_anakin(env, y, step);
	mlx_put_image_to_window(env->mlx.ptr, env->mlx.win, env->mlx.img, 0, 0);
	return (1);
}
