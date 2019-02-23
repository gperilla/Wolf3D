/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:16:55 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 15:14:20 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include "keys.h"
# include "data_path.h"

# include <sys/stat.h>
# include <math.h>
# include <pthread.h>
# include <string.h>
# include <fcntl.h>
# include "SDL_mixer.h"

# define WINX 1920
# define WINY 1080
# define NB_THRD 7
# define NB_SPRITES 10

# define FREQUENCY 44100

# define MOV_SPD 0.2
# define ROT_SPD 0.1

# define MARGE 0.075

# define PORTAL1_CLR 0xde0214
# define PORTAL2_CLR 0x14e002

typedef struct		s_vect
{
	float			x;
	float			y;
}					t_vect;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_buttn
{
	void			*img;
	char			*pix;
	int				wdth;
	int				hght;
}					t_buttn;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
	char			*pix;
	int				bpp;
	int				s_l;
	int				endian;
	t_buttn			cont;
	t_buttn			quit;
}					t_mlx;

typedef struct		s_cam
{
	t_vect			pos;
	float			camx;
	t_vect			dir;
	t_vect			plane;
	int8_t			mov;
	int8_t			rot;
	int8_t			straf;
	int8_t			crouch;
	int				crch_val;
	int8_t			jmp;
	int				jmp_val;
	int				vview;
	int8_t			sprint;
	int8_t			zoom;
}					t_cam;

typedef struct		s_ray
{
	t_vect			dir;
	t_vect			sd_dst;
	t_vect			dlt_dst;
	int				quart;
	t_vect			org_dir;
}					t_ray;

typedef struct		s_wall
{
	float			dst;
	int				height;
	int				start;
	int				end;
	float			d_y;
	float			wallx;
	t_point			tex;
	int				texnum;
}					t_wall;

typedef struct		s_thrd
{
	int				num;
	int				startx;
	int				endx;
}					t_thrd;

typedef struct		s_map
{
	int				width;
	int				height;
	int				**val;
}					t_map;

typedef struct		s_texture
{
	void			*img;
	char			*pix;
	int				wdth;
	int				hght;
	int				bpp;
	int				s_l;
	int				endian;
}					t_texture;

typedef struct		s_floor
{
	t_vect			wall;
	float			dstwall;
	float			dstplyr;
	float			currdst;
	float			weight;
	t_vect			current;
	t_point			tex;
	t_texture		texture;
}					t_floor;

typedef struct		s_sky
{
	int				start;
	float			dir;
	t_texture		texture;
}					t_sky;

typedef struct		s_sounds
{
	Mix_Music		*music;
	Mix_Chunk		*effect[10];
}					t_sounds;

typedef struct		s_sprite
{
	t_texture		tex;
	t_vect			pos;
	float			dst;
	t_vect			tmp;
	float			inv_d;
	t_vect			transf;
	int				hght;
	int				wdth;
	int				screenx;
	t_point			start;
	t_point			end;
	t_point			pos_tex;
	t_vect			div;
	float			vmov;
	int				d_y;
}					t_sprite;

typedef struct		s_portal
{
	t_point			pos;
	int				card;
	int				height;
	int				filter;
	float			d_y;
	float			wallx;
	int				side;
}					t_portal;

typedef struct		s_portalc
{
	int				y;
	int				end;
	unsigned int	color;
	unsigned int	c1;
	unsigned int	key;
	int				x0;
	int				y0;
}					t_portalc;

typedef struct		s_movep
{
	float			oldx;
	float			oldy;
	float			dx;
	float			dy;
}					t_movep;

typedef struct		s_env
{
	t_mlx			mlx;
	t_cam			cam;
	t_point			map;
	t_ray			ray;
	t_point			step;
	t_wall			wall;
	t_map			wmap;
	t_texture		tex[9];
	t_floor			floor;
	t_sky			sky;
	t_sprite		*sprt_ptr;
	t_sprite		sprt[NB_SPRITES];
	int				hit;
	int				side;
	float			mov_spd;
	float			rot_spd;
	int				mousex;
	t_thrd			thrd_nfo;
	pthread_t		thrd_id[NB_THRD];
	t_point			spr_thrd[NB_THRD];
	t_portal		portal[2];
	t_portalc		portalc;
	t_movep			movep;
	int				*pdst;
	int				pause;
	t_sounds		sound;
	float			*zbuffer;
	t_texture		end;
	int				autorun;
	int8_t			block;
	int				over;
	int				cheatbreak;
	int				cheatcolor;
	int				cheatp;
	int				loop;
}					t_env;

int					load_map(t_env *env, char *path);
void				my_putpixel(t_env *env, int x, int y, int color);
void				clean_exit(t_env *env);
void				ft_error(char *str);
int					ft_sign(float n);
int					parse_portals(t_env *env, char **line, int fd);
void				remove_existing_map(t_env *env);
int					parse_map_size(t_env *env, char **line);
int					parse_map_values(t_env *env, char **line, int fd);
int					parse_camera(t_env *env, char **line, int fd);
int					bandw_color(int color);
void				init_env(t_env *env, char *path);
void				world_tex_init(t_env *env);
void				init_walls_2(t_env *env);
void				init_walls_1(t_env *env);
void				init_sounds(t_env *env);
int					color_interpolate(int c1, int c2, float t);
int					my_get_pixel_color_tex(t_texture tex, int x, int y);
int					my_get_pixel_color_env(t_env *env, int x, int y);
void				init_img(t_env *env);
int					cmpfct(const void *a, const void *b);
void				draw_crosshair(t_env *env);
void				portal_coloring(t_env *env, int x);
void				portal_coloring_circle(t_env *env, int x, int p);
void				outside_portal_circle(t_env *env, int x, int p);
void				init_portal_coloring(t_env *env, int x, int p);
void				init_portal_coloring_side(t_env *env, int p);
void				apply_height_to_portal(t_env *env, int p);
void				calcul_portal_height(t_env *env, int x, int nbx,
	int nby);
void				calcul_portal_height_side(t_env *env, float *tmpy);
void				calcul_portal_height_not_side(t_env *env, float *tmpx);
void				same_direction_portals(t_env *env, int p);
void				reverse_direction_portals(t_env *env, int p);
void				one_quarter_turn_portals(t_env *env, int p, float *nbx,
	float *nby);
void				the_other_quarter_turn(t_env *env, int p, float *nbx,
	float *nby);
void				view_through_portal(t_env *env, int x, float *nbx,
	float *nby);
void				world_wall_texture_drawing(t_env *env, int x);
void				world_wall_texture_calc(t_env *env);
void				texture_calc_side(t_env *env);
void				world_wall_init_draw(t_env *env);
void				world_wall_dist(t_env *env, int x);
void				move_a_step(t_env *env, float *nbx, float *nby);
void				handle_sides(t_env *env, float *nbx, float *nby);
void				loop_the_map(t_env *env, int nbx, int nby);
void				world_step_calc(t_env *env);
void				world_floor_drawing(t_env *env, int x);
void				world_sky_init(t_env *env);
void				world_sky_drawing(t_env *env, int x);
void				*world_thread(void *arg);
void				world_sky(t_env *env, int x);
void				world_floor(t_env *env, int x);
void				world_wall(t_env *env, int x);
void				init_world_thread(t_env *env, int x);
void				*sprite_thread(void *arg);
int					end_game(t_env *env);
int					my_key_press(int key, t_env *env);
void				my_key_press3(int key, t_env *env);
void				my_key_press2(int key, t_env *env);
void				my_key_press1(int key, t_env *env);
void				quick_save(t_env *env);
int					my_destroy_notify(void);
int					my_button_press(int button, int x, int y, t_env *env);
int					my_pointer_motion(int x, int y, t_env *env);
int					my_key_release(int key, t_env *env);
void				move_through_other_quarter(t_env *env, int p);
void				move_through_one_quarter(t_env *env, int p);
void				move_through_opposite_dir(t_env *env, int p);
void				move_through_same_dir(t_env *env);
void				init_move_through(t_env *env, int p);
void				move_through_portal(t_env *env);
void				move_through_portal_p(t_env *env, int p);
void				crouch_and_jump(t_env *env);
void				walk_through_map(t_env *env);
void				rotations(t_env *env);
void				strafe(t_env *env);
void				move_straight(t_env *env);
void				search_portal_hit(t_env *env, float *nbx, float *nby);
void				shoot_portal_through_map(t_env *env);
void				init_portal_travelling(t_env *env, float *nbx, float *nby);
void				init_shoot_portal(t_env *env, int i);
void				shoot_portal(t_env *env, int p);
void				create_portal(t_env *env, int p);
void				create_block(t_env *env);
int					game_loop(t_env *env);
void				game_paused(t_env *env);
void				multithreading(t_env *env);
void				draw_block(t_env *env);

#endif
