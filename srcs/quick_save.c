/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_save.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:49:10 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:07:11 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	quick_save(t_env *env)
{
	int		x;
	int		y;
	FILE	*fd;

	mkdir("saves", 0755);
	fd = fopen("saves/qsave", "w");
	fprintf(fd, "map: %d %d\n", env->wmap.width, env->wmap.height);
	x = -1;
	while (++x < env->wmap.height)
	{
		y = -1;
		while (++y < env->wmap.width)
		{
			fprintf(fd, "%d", env->wmap.val[x][y]);
			if (y < env->wmap.width - 1)
				fprintf(fd, " ");
		}
		fprintf(fd, "\n");
	}
	fprintf(fd, "pos: %lf %lf\n", env->cam.pos.x, env->cam.pos.y);
	fprintf(fd, "dir: %lf %lf\n", env->cam.dir.x, env->cam.dir.y);
	fprintf(fd, "por: %d %d %d %d %d %d\n", env->portal[0].pos.x,
	env->portal[0].pos.y, env->portal[0].card,
		env->portal[1].pos.x, env->portal[1].pos.y, env->portal[1].card);
	fclose(fd);
}
