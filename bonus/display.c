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

void	debug_map(t_world *world)
{
	int i, j;

	for (i = 0; i < world->map_height; i++)
	{
		for (j = 0; j < world->map_width; j++)
		{
			printf("%d ", world->map[i][j]);
		}
		printf("\n");
	}
}

void	debug_sprites(t_world *world)
{
	int i;

	printf("Sprites:\n");
	for (i = 0; i < world->nb_sprites; i++)
	{
		printf("(%2d, %2d) Distance: %f\n", world->sprites[i].pos[0], world->sprites[i].pos[1], world->sprites[i].distance);
	}
}

void	draw_square(t_world *world, int x, int y, int cell)
{
	int		i;
	int		j;
	int		color;
	int		unit;

	unit = (int)(100 / world->map_width);
	if (cell == 0)
		color = 0xFFFFFF;
	else if (cell == 1)
		color = 0x0000FF;
	else
		color = (cell == 2) ? 0x9F0000 : 0x009F00;
	j = y;
	while (j < y + unit)
	{
		i = x;
		while (i < x + unit)
		{
			if (cell >= 0)
				set_screen_pixel(world->screen, i, j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_world *world, int offset_x, int offset_y)
{
	int		i;
	int		j;
	int		unit;

	unit = (int)(100 / world->map_width);
	j = 0;
	while (j < world->map_height)
	{
		i = 0;
		while (i < world->map_width)
		{
			draw_square(world, offset_x + j * unit,
				offset_y + i * unit, world->map[i][j]);
			i++;
		}
		j++;
	}
	draw_square(world, (int)(offset_x + world->pos[1] * unit),
		(int)(offset_y + world->pos[0] * unit), 3);
}
