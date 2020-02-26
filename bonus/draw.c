/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_row_floor(t_world *world, int j, double left[2], double right[2])
{
	double	row_dist;
	double	step[2];
	double	floor_pos[2];
	int		color;
	int		i;

	row_dist = 0.5 * (1 + world->jump_coeff)
		* world->scr_height / (j - world->scr_height / 2);
	step[0] = row_dist * (right[0] - left[0]) / world->scr_width;
	step[1] = row_dist * (right[1] - left[1]) / world->scr_width;
	floor_pos[0] = world->pos[0] + row_dist * left[0];
	floor_pos[1] = world->pos[1] + row_dist * left[1];
	i = 0;
	while (i < world->scr_width)
	{
		color = get_tex_color(world->texture_floor,
			floor_pos[0] - floor(floor_pos[0]),
			floor_pos[1] - floor(floor_pos[1]),
			((j - world->scr_height / 2) * 3.0 / world->scr_height));
		set_screen_pixel(world->screen, i++, j, color);
		floor_pos[0] += step[0];
		floor_pos[1] += step[1];
	}
}

void	draw_floor(t_world *world)
{
	int		j;
	double	left[2];
	double	right[2];

	left[0] = world->dir[0] - world->cam_plane[0];
	left[1] = world->dir[1] - world->cam_plane[1];
	right[0] = world->dir[0] + world->cam_plane[0];
	right[1] = world->dir[1] + world->cam_plane[1];
	j = world->scr_height / 2;
	while (j < world->scr_height)
		draw_row_floor(world, j++, left, right);
}

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
	draw_floor(world);
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
		draw_minimap(world, 20, 20, 100);
		draw_life(world, -20, 20, 200);
		draw_gun(world, world->ctrls.space);
		mlx_put_image_to_window(world->mlx.ptr, world->mlx.win,
			world->screen.ptr, 0, 0);
	}
}
