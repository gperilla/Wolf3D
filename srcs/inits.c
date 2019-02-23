/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:14:44 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:21:15 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_sounds(t_env *env)
{
	if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
		== -1)
		ft_error("SDL");
	env->sound.music = Mix_LoadMUS(BGM);
	Mix_PlayMusic(env->sound.music, -1);
	Mix_AllocateChannels(10);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	env->sound.effect[0] = Mix_LoadWAV(S_E1);
	env->sound.effect[1] = Mix_LoadWAV(S_E2);
	env->sound.effect[2] = Mix_LoadWAV(S_E3);
	env->sound.effect[3] = Mix_LoadWAV(S_E4);
	env->sound.effect[4] = Mix_LoadWAV(S_E5);
	env->sound.effect[5] = Mix_LoadWAV(S_EJ2);
	env->sound.effect[6] = Mix_LoadWAV(S_EJ1);
}

void	init_walls_1(t_env *env)
{
	env->tex[0].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL0,
		&env->tex[0].wdth, &env->tex[0].hght);
	env->tex[0].pix = mlx_get_data_addr(env->tex[0].img, &env->tex[0].bpp,
		&env->tex[0].s_l, &env->tex[0].endian);
	env->tex[1].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL1,
		&env->tex[1].wdth, &env->tex[1].hght);
	env->tex[1].pix = mlx_get_data_addr(env->tex[1].img, &env->tex[1].bpp,
		&env->tex[1].s_l, &env->tex[1].endian);
	env->tex[2].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL2,
		&env->tex[2].wdth, &env->tex[2].hght);
	env->tex[2].pix = mlx_get_data_addr(env->tex[2].img, &env->tex[2].bpp,
		&env->tex[2].s_l, &env->tex[2].endian);
	env->tex[3].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL3,
		&env->tex[3].wdth, &env->tex[3].hght);
	env->tex[3].pix = mlx_get_data_addr(env->tex[3].img, &env->tex[3].bpp,
		&env->tex[3].s_l, &env->tex[3].endian);
	env->tex[4].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL4,
		&env->tex[4].wdth, &env->tex[4].hght);
	env->tex[4].pix = mlx_get_data_addr(env->tex[4].img, &env->tex[4].bpp,
		&env->tex[4].s_l, &env->tex[4].endian);
}

void	init_walls_2(t_env *env)
{
	env->tex[5].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL5,
		&env->tex[5].wdth, &env->tex[5].hght);
	env->tex[5].pix = mlx_get_data_addr(env->tex[5].img, &env->tex[5].bpp,
		&env->tex[5].s_l, &env->tex[5].endian);
	env->tex[6].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL6,
		&env->tex[6].wdth, &env->tex[6].hght);
	env->tex[6].pix = mlx_get_data_addr(env->tex[6].img, &env->tex[6].bpp,
		&env->tex[6].s_l, &env->tex[6].endian);
	env->tex[7].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL7,
		&env->tex[7].wdth, &env->tex[7].hght);
	env->tex[7].pix = mlx_get_data_addr(env->tex[7].img, &env->tex[7].bpp,
		&env->tex[7].s_l, &env->tex[7].endian);
	env->tex[8].img = mlx_xpm_file_to_image(env->mlx.ptr, WALL8,
		&env->tex[8].wdth, &env->tex[8].hght);
	env->tex[8].pix = mlx_get_data_addr(env->tex[8].img, &env->tex[8].bpp,
		&env->tex[8].s_l, &env->tex[8].endian);
}

void	world_tex_init(t_env *env)
{
	init_walls_1(env);
	init_walls_2(env);
	env->sky.texture.img = mlx_xpm_file_to_image(env->mlx.ptr, "data/skyd.xpm",
		&env->sky.texture.wdth, &env->sky.texture.hght);
	env->sky.texture.pix = mlx_get_data_addr(env->sky.texture.img,
		&env->sky.texture.bpp, &env->sky.texture.s_l, &env->sky.texture.endian);
	env->end.img = mlx_xpm_file_to_image(env->mlx.ptr, END,
		&env->end.wdth, &env->end.hght);
	env->end.pix = mlx_get_data_addr(env->end.img,
		&env->end.bpp, &env->end.s_l, &env->end.endian);
}

int		load_map(t_env *env, char *path)
{
	int		fd;
	char	*line;

	remove_existing_map(env);
	if (!(fd = open(path, O_RDONLY)))
		return ((env->over = 1));
	if (get_next_line(fd, &line) <= 0)
		return ((env->over = 1));
	if (parse_map_size(env, &line) == 1)
		return (1);
	if (parse_map_values(env, &line, fd) == 1)
		return (1);
	if (parse_camera(env, &line, fd) == 1)
		return (1);
	env->cam.plane.x = env->cam.dir.x * cos(-M_PI / 2)
		- env->cam.dir.y * sin(-M_PI / 2);
	env->cam.plane.y = env->cam.dir.x * sin(-M_PI / 2)
		+ env->cam.dir.y * cos(-M_PI / 2);
	env->cam.plane.x *= 0.77;
	env->cam.plane.y *= 0.77;
	if (parse_portals(env, &line, fd) == 1)
		return (1);
	return (0);
}
