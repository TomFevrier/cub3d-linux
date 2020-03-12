/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_cell_init(t_world *world, int i, int j, t_bool *cam_parsed)
{
	if (j >= ft_strlen(world->char_map[i]) || world->char_map[i][j] <= ' ')
		world->map[i][j] = -1;
	else if (ft_indexof("012", world->char_map[i][j]) >= 0)
		world->map[i][j] = world->char_map[i][j] - '0';
	else if (ft_indexof("NWSE", world->char_map[i][j]) >= 0)
	{
		if (*cam_parsed)
			parsing_error(world, "Map must only contain one player", 0);
		else
		{
			world->cam_dir = ft_indexof("NWSE", world->char_map[i][j]);
			world->map[i][j] = 0;
			world->pos[0] = i;
			world->pos[1] = j;
			*cam_parsed = TRUE;
		}
	}
	if (world->map[i][j] == 2)
		world->nb_sprites++;
}

void	map_init(t_world *world)
{
	int		i;
	int		j;
	t_bool	cam_parsed;

	cam_parsed = FALSE;
	world->nb_sprites = 0;
	world->map = ft_calloc(world->map_height, sizeof(int *));
	i = 0;
	while (i < world->map_height)
	{
		world->map[i] = ft_calloc(world->map_width, sizeof(int));
		j = 0;
		while (j < world->map_width)
			map_cell_init(world, i, j++, &cam_parsed);
		free(world->char_map[i]);
		i++;
	}
	if (!cam_parsed)
		parsing_error(world, "Player position is not defined", 0);
	free(world->char_map);
}

void	parse_map_row(t_world *world, int i)
{
	int		j;

	j = 0;
	while (world->raw_map[j] && world->raw_map[j] != '\n')
		j++;
	world->char_map[i] = ft_substr(world->raw_map, 0, j);
	world->raw_map += j + 1;
	j = 0;
	while (world->char_map[i][j])
	{
		if (ft_indexof(" \t012NWSE", world->char_map[i][j]) < 0)
			parsing_error(world, "Map contains invalid characters", 0);
		j++;
	}
	if (ft_strlen(world->char_map[i]) > world->map_width)
		world->map_width = ft_strlen(world->char_map[i]);
}

t_bool	parse_map(t_world *world)
{
	int		i;
	char	*ptr;

	i = 0;
	world->map_height = 0;
	while (world->raw_map[i])
	{
		if (world->raw_map[i] == '\n')
			world->map_height++;
		i++;
	}
	if (!(world->char_map = ft_calloc(world->map_height, sizeof(char *))))
		return (FALSE);
	ptr = world->raw_map;
	i = 0;
	world->map_width = 0;
	while (i < world->map_height)
		parse_map_row(world, i++);
	free(ptr);
	map_init(world);
	check_map(world);
	if (world->error)
		quit(world, ERROR);
	return (TRUE);
}

void	read_map_row(t_world *world, char *ptr)
{
	char	*tmp;

	check_missing(world);
	ptr = ft_trim(ptr);
	if (!world->raw_map)
		world->raw_map = ft_strdup(ptr);
	else
	{
		tmp = world->raw_map;
		world->raw_map = ft_strjoin(world->raw_map, ptr);
		free(tmp);
	}
	tmp = world->raw_map;
	world->raw_map = ft_strjoin(world->raw_map, "\n");
	free(tmp);
}
