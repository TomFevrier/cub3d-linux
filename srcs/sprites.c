/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_distances(t_world *world)
{
	int	i;

	i = 0;
	while (i < world->nb_sprites)
	{
		world->sprites[i].distance =
			pow(world->pos[0] - world->sprites[i].pos[0], 2)
			+ pow(world->pos[1] - world->sprites[i].pos[1], 2);
		i++;
	}
}

void	sort_sprites(t_world *world)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < world->nb_sprites)
	{
		j = 0;
		while (j < world->nb_sprites - i - 1)
		{
			if (world->sprites[i].distance < world->sprites[i + 1].distance)
			{
				tmp = world->sprites[i];
				world->sprites[i] = world->sprites[i + 1];
				world->sprites[i + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	draw_line_sprite(t_world *world, t_spritedata data, int i,
	int bbox_x[2])
{
	int		bbox_y[2];
	int		j;
	int		color;

	bbox_y[0] = world->scr_height / 2 - data.sprite_size / 2;
	bbox_y[1] = world->scr_height / 2 + data.sprite_size / 2;
	j = (bbox_y[0] < 0) ? 0 : bbox_y[0];
	while (j < (bbox_y[1] >= world->scr_height
		? world->scr_height - 1 : bbox_y[1]))
	{
		color = get_tex_color(world->sprites[data.index].texture,
			((i - bbox_x[0]) * 1.0) / (bbox_x[1] - bbox_x[0]),
			((j - bbox_y[0]) * 1.0) / (bbox_y[1] - bbox_y[0]));
		if (color != 0)
			set_screen_pixel(world->screen, i, j, color);
		j++;
	}
}

void	draw_sprite(t_world *world, t_spritedata data)
{
	int		bbox_x[2];
	int		i;

	bbox_x[0] = data.sprite_x - data.sprite_size / 2;
	bbox_x[1] = data.sprite_x + data.sprite_size / 2;
	i = (bbox_x[0] < 0) ? 0 : bbox_x[0];
	while (i <= (bbox_x[1] >= world->scr_width ?
		world->scr_width - 1 : bbox_x[1]))
	{
		if (data.transform[1] > 0 && data.transform[1] < world->depth_buffer[i])
			draw_line_sprite(world, data, i, bbox_x);
		i++;
	}
}

void	draw_sprites(t_world *world)
{
	t_spritedata	data;
	double			sprite_pos[2];
	double			det;

	compute_distances(world);
	sort_sprites(world);
	data.index = 0;
	while (data.index < world->nb_sprites)
	{
		sprite_pos[0] = world->sprites[data.index].pos[0] + 0.5 - world->pos[0];
		sprite_pos[1] = world->sprites[data.index].pos[1] + 0.5 - world->pos[1];
		det = 1.0 / (world->cam_plane[0] * world->dir[1]
			- world->dir[0] * world->cam_plane[1]);
		data.transform[0] = det * (world->dir[1] * sprite_pos[0]
			- world->dir[0] * sprite_pos[1]);
		data.transform[1] = det * (-world->cam_plane[1] * sprite_pos[0]
			+ world->cam_plane[0] * sprite_pos[1]);
		data.sprite_x = (int)((world->scr_width / 2) *
			(1 + data.transform[0] / data.transform[1]));
		data.sprite_size = abs((int)(world->scr_height / data.transform[1]));
		draw_sprite(world, data);
		data.index++;
	}
}
