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

void	check_missing(t_world *world)
{
	if (!world->scr_width)
		parsing_error(world, "Resolution must be defined before the map", 0);
	else if (!world->texture_floor.data)
		parsing_error(world, "Floor texture must be defined before the map", 0);
	else if (!world->texture_sky.data)
		parsing_error(world, "Sky texture must be defined before the map", 0);
	else if (!world->textures[N].data)
		parsing_error(world, "North texture must be defined before the map", 0);
	else if (!world->textures[W].data)
		parsing_error(world, "West texture must be defined before the map", 0);
	else if (!world->textures[S].data)
		parsing_error(world, "South texture must be defined before the map", 0);
	else if (!world->textures[E].data)
		parsing_error(world, "East texture must be defined before the map", 0);
	else if (!world->music_file)
		parsing_error(world, "Music file must be defined before the map", 0);
}

t_bool	check_map_row(t_world *world, int i, int j, t_bool cam_parsed)
{
	int		min;

	min = ft_strlen(world->char_map[i - 1])
		< ft_strlen(world->char_map[i + 1])
		? ft_strlen(world->char_map[i - 1])
		: ft_strlen(world->char_map[i + 1]);
	if ((j == 0 || (j >= min && j < ft_strlen(world->char_map[i]))) &&
		world->char_map[i][j] != '1')
		return (FALSE);
	else if (ft_indexof("012NWSE", world->char_map[i][j]) < 0)
		return (FALSE);
	else if (ft_indexof("NWSE", world->char_map[i][j]) >= 0)
	{
		if (cam_parsed)
			return (FALSE);
		world->cam_dir = ft_indexof("NWSE", world->char_map[i][j]);
		world->char_map[i][j] = '0';
		world->pos[0] = i;
		world->pos[1] = j;
		cam_parsed = TRUE;
	}
	return (TRUE);
}

t_bool	check_map(t_world *world)
{
	int		i;
	int		j;
	t_bool	cam_parsed;

	cam_parsed = FALSE;
	j = 0;
	while (j < ft_strlen(world->char_map[0]))
		if (world->char_map[0][j++] != '1')
			return (FALSE);
	i = 1;
	while (i < world->map_height - 1)
	{
		j = 0;
		while (j < ft_strlen(world->char_map[i]))
			if (!check_map_row(world, i, j++, cam_parsed))
				return (FALSE);
		i++;
	}
	j = 0;
	while (j < ft_strlen(world->char_map[world->map_height - 1]))
		if (world->char_map[world->map_height - 1][j++] != '1')
			return (FALSE);
	return (TRUE);
}
