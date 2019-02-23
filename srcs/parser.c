/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:03:33 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:38:16 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		parse_portals(t_env *env, char **line, int fd)
{
	int i;

	if (get_next_line(fd, &(*line)) <= 0)
		return ((env->over = 1));
	if (ft_strncmp((*line), "por: ", 5) != 0)
		return ((env->over = 1));
	i = 5;
	env->portal[0].pos.x = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->portal[0].pos.y = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->portal[0].card = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->portal[1].pos.x = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->portal[1].pos.y = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->portal[1].card = ft_atoi((*line) + i);
	free((*line));
	return (0);
}

void	remove_existing_map(t_env *env)
{
	int x;

	if (env->wmap.val)
	{
		x = -1;
		while (++x < env->wmap.height)
			free(env->wmap.val[x]);
		free(env->wmap.val);
	}
}

int		parse_map_size(t_env *env, char **line)
{
	int i;

	if (ft_strncmp((*line), "map: ", 5) != 0)
		return ((env->over = 1));
	i = 5;
	env->wmap.width = ft_atoi((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->wmap.height = ft_atoi((*line) + i);
	if (env->wmap.height <= 0 || env->wmap.width <= 0)
		return ((env->over = 1));
	free((*line));
	if (!(env->wmap.val = malloc(sizeof(int*) * env->wmap.height)))
		exit(0);
	return (0);
}

int		parse_map_values(t_env *env, char **line, int fd)
{
	int x;
	int y;
	int i;

	x = -1;
	while (++x < env->wmap.height)
	{
		y = -1;
		i = 0;
		if (!(env->wmap.val[x] = malloc(sizeof(int) * env->wmap.width)))
			exit(0);
		if (get_next_line(fd, &(*line)) <= 0)
			return ((env->over = 1));
		while (++y < env->wmap.width)
		{
			env->wmap.val[x][y] = ft_atoi((*line) + i);
			while ((*line)[++i] && (*line)[i] != ' ')
				continue;
		}
		free((*line));
	}
	return (0);
}

int		parse_camera(t_env *env, char **line, int fd)
{
	int i;

	if (get_next_line(fd, &(*line)) <= 0)
		return ((env->over = 1));
	if (ft_strncmp((*line), "pos: ", 5) != 0)
		return ((env->over = 1));
	i = 5;
	env->cam.pos.x = atof((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->cam.pos.y = atof((*line) + i);
	free((*line));
	if (get_next_line(fd, &(*line)) <= 0)
		return ((env->over = 1));
	if (ft_strncmp((*line), "dir: ", 5) != 0)
		return ((env->over = 1));
	i = 5;
	env->cam.dir.x = atof((*line) + i);
	while ((*line)[++i] && (*line)[i] != ' ')
		continue;
	env->cam.dir.y = atof((*line) + i);
	free((*line));
	return (0);
}
