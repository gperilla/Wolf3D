/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 15:49:10 by gperilla          #+#    #+#             */
/*   Updated: 2018/10/07 17:21:57 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_env(t_env *env, char *path)
{
	ft_bzero(env, sizeof(t_env));
	init_sounds(env);
	load_map(env, path);
	env->mlx.ptr = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.ptr, WINX, WINY, "Wolf3D");
	env->mlx.img = NULL;
	env->mlx.pix = NULL;
	env->cam.dir.x = 1;
	env->cam.dir.y = 0;
	env->cam.plane.x = 0;
	env->cam.plane.y = -0.76;
	env->mov_spd = MOV_SPD;
	env->rot_spd = ROT_SPD;
	env->mousex = WINX / 2;
	env->block = 1;
	env->sprt_ptr = env->sprt;
	env->portal[0].filter = PORTAL1_CLR;
	env->portal[1].filter = PORTAL2_CLR;
	env->mlx.cont.img = mlx_xpm_file_to_image(env->mlx.ptr, "data/continue.xpm",
		&env->mlx.cont.wdth, &env->mlx.cont.hght);
	env->mlx.quit.img = mlx_xpm_file_to_image(env->mlx.ptr, "data/quit.xpm",
		&env->mlx.quit.wdth, &env->mlx.quit.hght);
	world_tex_init(env);
}

int		main(int argc, char **argv)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		ft_error("malloc");
	if (argc != 2)
	{
		ft_printf("usage: ./wolf3D map_path\n");
		exit(0);
	}
	init_env(env, argv[1]);
	if (!(env->zbuffer = malloc(sizeof(float) * WINX)))
		ft_error("malloc");
	if (!(env->pdst = malloc(sizeof(int) * 2)))
		ft_error("malloc");
	mlx_hook(env->mlx.win, 2, (1L << 0), my_key_press, env);
	mlx_hook(env->mlx.win, 3, (1L << 1), my_key_release, env);
	mlx_hook(env->mlx.win, 6, (1L << 6), my_pointer_motion, env);
	mlx_hook(env->mlx.win, 17, (0L), my_destroy_notify, env);
	mlx_hook(env->mlx.win, 4, (1L << 2), my_button_press, env);
	mlx_loop_hook(env->mlx.ptr, game_loop, env);
	mlx_loop(env->mlx.ptr);
	return (0);
}
