/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:19:22 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:18:27 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_img(t_env *env)
{
	mlx_clear_window(env->mlx.ptr, env->mlx.win);
	if (env->mlx.img)
		mlx_destroy_image(env->mlx.ptr, env->mlx.img);
	env->mlx.img = mlx_new_image(env->mlx.ptr, WINX, WINY);
	env->mlx.pix = mlx_get_data_addr(env->mlx.img, &env->mlx.bpp, &env->mlx.s_l,
		&env->mlx.endian);
}

int		cmpfct(const void *a, const void *b)
{
	const t_sprite *sa;
	const t_sprite *sb;

	sa = a;
	sb = b;
	return ((int)((sb->dst - sa->dst) * 100));
}

void	draw_crosshair(t_env *env)
{
	int x;
	int y;
	int loop;
	int color;

	x = WINX / 2 - 5;
	y = WINY / 2 - 5;
	loop = -1;
	color = 0xFF0000;
	while (++loop <= 10)
	{
		my_putpixel(env, x + loop, y + loop, color);
		my_putpixel(env, x + 10 - loop, y + loop, color);
	}
}
