/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:00:54 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:18:06 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	clean_exit(t_env *env)
{
	if (!env)
		exit(1);
	Mix_FreeMusic(env->sound.music);
	Mix_FreeChunk(env->sound.effect[0]);
	free(env);
	Mix_CloseAudio();
	exit(0);
}

void	ft_error(char *str)
{
	ft_printf("error %s\n", str);
	clean_exit(NULL);
}

int		ft_sign(float n)
{
	return ((n > 0) - (n < 0));
}

int		bandw_color(int color)
{
	int	r;
	int	g;
	int	b;
	int	moy;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0x00FF00) >> 8;
	b = (color & 0x0000FF);
	moy = .27 * r + .57 * g + .15 * b;
	return ((color & 0xFF000000) | (moy << 16) | (moy << 8) | moy);
}

int		color_interpolate(int c1, int c2, float t)
{
	int r;
	int v;
	int b;

	r = (1 - t) * ((c1 & 0xFF0000) >> 16) + t * ((c2 & 0xFF0000) >> 16);
	v = (1 - t) * ((c1 & 0x00FF00) >> 8) + t * ((c2 & 0x00FF00) >> 8);
	b = (1 - t) * ((c1 & 0x0000FF)) + t * ((c2 & 0x0000FF));
	return ((r << 16) | (v << 8) | (b));
}
