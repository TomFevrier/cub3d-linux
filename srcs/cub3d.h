/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:18:13 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 15:15:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>

# include "../get_next_line/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

# define KEY_A 113
# define KEY_S 115
# define KEY_D 100
# define KEY_W 122
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef int			t_bool;

typedef enum		e_side
{
	N,
	W,
	S,
	E
}					t_side;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_dda
{
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
	int		map_pos[2];
	int		step[2];
}					t_dda;

typedef struct		s_texdata
{
	double	wall_dist;
	double	wall_x;
	int		line_height;
	t_side	side;
}					t_texdata;

typedef struct		s_spritedata
{
	double	transform[2];
	int		sprite_x;
	int		sprite_size;
	int		index;
}					t_spritedata;

typedef struct		s_ctrls
{
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	t_bool	left;
	t_bool	right;
}					t_ctrls;

typedef struct		s_img
{
	char	*filename;
	void	*ptr;
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		size_line;
	t_bool	endian;
}					t_img;

typedef struct		s_sprite
{
	int		pos[2];
	double	distance;
	t_img	texture;
}					t_sprite;

typedef struct		s_world
{
	t_mlx			mlx;
	int				fd;
	t_bool			error;
	int				scr_width;
	int				scr_height;
	int				map_width;
	int				map_height;
	char			*raw_map;
	char			**char_map;
	int				**map;
	int				color_floor;
	int				color_ceiling;
	t_img			textures[4];
	t_img			texture_sprite;
	int				nb_sprites;
	t_sprite		*sprites;
	t_img			screen;
	t_ctrls			ctrls;
	int				nb_pixels;
	double			*depth_buffer;
	double			pos[2];
	double			dir[2];
	double			cam_plane[2];
	t_side			cam_dir;
	t_bool			save;
	int				fd_save;
}					t_world;

t_world				*world_init(int argc, char **argv);

t_bool				init_other_stuff(t_world *world);

void				parse_line(t_world *world, char *line, int line_nb,
					int res);

void				parsing_error(t_world *world, char *message, int line_nb);
t_bool				parse_map(t_world *world);
void				read_map_row(t_world *world, char *ptr);

void				check_missing(t_world *world);
void				check_map(t_world *world);

void				draw(t_world *world);

void				run_dda(t_world *world, int i, double ray[2]);

void				draw_sprites(t_world *world);

int					key_pressed(int key, t_world *world);
int					key_released(int key, t_world *world);
int					quit(t_world *world, t_bool exit_value);

t_bool				move(t_world *world);
t_bool				rotate(t_world *world);

int					ft_strlen(char *str);
int					ft_indexof(char *str, char c);
int					ft_strcmp(char *s1, char *s2);
int					ft_atoi_easy(char *str);
char				*ft_trim(char *str);
char				*ft_remove_spaces(char *str);

void				set_screen_pixel(t_img screen, int i, int j, int color);
int					get_screen_pixel(t_img screen, int i, int j);
int					get_tex_color(t_img tex, double u, double v);
void				load_textures(t_world *world);

void				number_to_mem(char *dest, int nb, int nb_bytes);
void				write_bmp_header(t_world *world);
void				flip_pixels(t_world *world);

void				*ft_calloc(int count, int size);
void				free_world(t_world *world);

#endif
