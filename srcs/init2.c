/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	sprites_init(t_world *world)
{
	int		i;
	int		j;
	int		index;

	if (!(world->sprites = ft_calloc(world->nb_sprites, sizeof(t_sprite))))
		return (FALSE);
	index = 0;
	i = 0;
	while (i < world->map_height)
	{
		j = 0;
		while (j < world->map_width)
		{
			if (world->map[i][j] == 2)
			{
				world->sprites[index].texture = world->texture_sprite;
				world->sprites[index].pos[0] = i;
				world->sprites[index].pos[1] = j;
				index++;
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

void	cam_init(t_world *world)
{
	if (world->cam_dir == E || world->cam_dir == W)
	{
		world->dir[0] = 0;
		world->dir[1] = (world->cam_dir == E) ? 1 : -1;
		world->cam_plane[0] = (world->cam_dir == E) ? 0.66 : -0.66;
		world->cam_plane[1] = 0;
	}
	else
	{
		world->dir[0] = (world->cam_dir == S) ? 1 : -1;
		world->dir[1] = 0;
		world->cam_plane[0] = 0;
		world->cam_plane[1] = (world->cam_dir == S) ? -0.66 : 0.66;
	}
}

t_bool	screen_init(t_world *world)
{
	if (!(world->screen.ptr = mlx_new_image(world->mlx.ptr,
		world->scr_width, world->scr_height)))
		return (FALSE);
	if (!(world->screen.data = mlx_get_data_addr(world->screen.ptr,
		&(world->screen.bpp), &(world->screen.size_line),
		&(world->screen.endian))))
		return (FALSE);
	return (TRUE);
}

t_bool	init_other_stuff(t_world *world)
{
	if (!parse_map(world))
		return (FALSE);
	cam_init(world);
	if (!(world->mlx.ptr = mlx_init()))
		return (FALSE);
	load_textures(world);
	if (!sprites_init(world))
		return (FALSE);
	if (!(world->depth_buffer = ft_calloc(world->scr_width, sizeof(double))))
		return (FALSE);
	if (!screen_init(world))
		return (FALSE);
	world->nb_pixels = world->scr_width * world->scr_height *
		(world->screen.bpp >> 3);
	if (world->save)
	{
		world->fd_save = open("cub3d.bmp", O_WRONLY | O_CREAT, 0777);
		write_bmp_header(world);
	}
	else if (!(world->mlx.win = mlx_new_window(world->mlx.ptr, world->scr_width,
		world->scr_height, "Cub3D")))
		return (FALSE);
	return (TRUE);
}
