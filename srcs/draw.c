/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 13:28:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_world *world)
{
	int		i;
	double	camera_x;
	double	ray[2];

	i = 0;
	while (i < world->scr_width)
	{
		camera_x = 2.0 * i / world->scr_width - 1;
		ray[0] = world->dir[0] + world->cam_plane[0] * camera_x;
		ray[1] = world->dir[1] + world->cam_plane[1] * camera_x;
		run_dda(world, i++, ray);
	}
}

void	draw(t_world *world)
{
	draw_walls(world);
	draw_sprites(world);
	if (world->save)
	{
		flip_pixels(world);
		write(world->fd_save, world->screen.data, world->nb_pixels);
		close(world->fd_save);
	}
	else
	{
		mlx_put_image_to_window(world->mlx.ptr, world->mlx.win,
			world->screen.ptr, 0, 0);
	}
}
