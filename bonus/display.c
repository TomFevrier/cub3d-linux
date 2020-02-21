/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_text(t_world *world, int x, int y, char *text)
{
	x -= ft_strlen(text) * 5;
	mlx_string_put(world->mlx.ptr, world->mlx.win, x, y, 0xFFFFFF, text);
}

void	draw_square(t_world *world, int x, int y, int cell)
{
	int		i;
	int		j;
	int		color;

	if (cell == 0)
		color = 0xFFFFFF;
	else if (cell == 1)
		color = 0x0000FF;
	else
		color = (cell == 2) ? 0x9F0000 : 0x009F00;
	j = y;
	while (j < y + world->minimap_unit)
	{
		i = x;
		while (i < x + world->minimap_unit)
		{
			if (cell >= 0)
				set_screen_pixel(world->screen, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_world *world, int offset_x, int offset_y, int width)
{
	int		i;
	int		j;

	world->minimap_unit = (int)(width / world->map_width);
	if (offset_x < 0)
		offset_x = world->scr_width + offset_x - width;
	if (offset_y < 0)
		offset_y = world->scr_height + offset_y
		- world->map_height * world->minimap_unit;
	j = 0;
	while (j < world->map_height)
	{
		i = 0;
		while (i < world->map_width)
		{
			draw_square(world, offset_x + j * world->minimap_unit,
				offset_y + i * world->minimap_unit, world->map[i][j]);
			i++;
		}
		j++;
	}
	draw_square(world, (int)(offset_x + world->pos[1] * world->minimap_unit),
		(int)(offset_y + world->pos[0] * world->minimap_unit), 3);
}

void	draw_life(t_world *world, int offset_x, int offset_y, int width)
{
	int		i;
	int		j;
	int		color;

	if (offset_x < 0)
		offset_x = world->scr_width + offset_x - width;
	if (offset_y < 0)
		offset_y = world->scr_height + offset_y - width / 10;
	j = offset_y;
	while (j < offset_y + width / 10)
	{
		i = offset_x;
		while (i < offset_x + width)
		{
			color = (i - offset_x < world->life * (width / 100))
				? 0x9F0000 : 0xFFFFFF;
			set_screen_pixel(world->screen, i++, j, color);
		}
		j++;
	}
}
