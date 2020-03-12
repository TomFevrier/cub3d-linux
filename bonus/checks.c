/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_error(t_world *world, char *message, int line_nb)
{
	char	c;

	if (world->error)
		return ;
	write(1, "Error\n", 6);
	write(1, message, ft_strlen(message));
	if (line_nb > 0)
	{
		write(1, " on line ", 9);
		c = line_nb / 10 + '0';
		if (c != '0')
			write(1, &c, 1);
		c = line_nb % 10 + '0';
		write(1, &c, 1);
	}
	write(1, "\n", 1);
	world->error = TRUE;
}

void	check_missing(t_world *world)
{
	if (!world->scr_width)
		parsing_error(world, "Resolution must be defined before the map", 0);
	else if (!world->texture_floor.filename)
		parsing_error(world, "Floor texture must be defined before the map", 0);
	else if (!world->texture_sky.filename)
		parsing_error(world, "Sky texture must be defined before the map", 0);
	else if (!world->textures[N].filename)
		parsing_error(world, "North texture must be defined before the map", 0);
	else if (!world->textures[W].filename)
		parsing_error(world, "West texture must be defined before the map", 0);
	else if (!world->textures[S].filename)
		parsing_error(world, "South texture must be defined before the map", 0);
	else if (!world->textures[E].filename)
		parsing_error(world, "East texture must be defined before the map", 0);
	else if (!world->texture_sprite.filename)
		parsing_error(world, "Sprite texture must be defined before the map",
		0);
	else if (!world->texture_portal.filename)
		parsing_error(world, "Portal texture must be defined before the map",
		0);
	else if (!world->music_file)
		parsing_error(world, "Music file must be defined before the map", 0);
}

t_bool	check_cell(t_world *world, int i, int j)
{
	return (!((i == 0 || j == 0
		|| i == world->map_height - 1 || j == world->map_width - 1
		|| world->map[i - 1][j] == -1 || world->map[i + 1][j] == -1
		|| world->map[i][j - 1] == -1 || world->map[i][j + 1] == -1)
		&& world->map[i][j] != 1 && world->map[i][j] != -1));
}

void	check_map(t_world *world)
{
	int		i;
	int		j;

	i = 0;
	while (i < world->map_height)
	{
		j = 0;
		while (j < world->map_width)
		{
			if (!check_cell(world, i, j))
				parsing_error(world, "Map is invalid", 0);
			j++;
		}
		i++;
	}
}
