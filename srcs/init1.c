/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(t_world *world)
{
	int		i;
	int		j;

	world->nb_sprites = 0;
	world->map = malloc(world->map_height * sizeof(int *));
	i = 0;
	while (i < world->map_height)
	{
		world->map[i] = malloc(world->map_width * sizeof(int));
		j = 0;
		while (j < world->map_width)
		{
			if (j < ft_strlen(world->char_map[i]))
				world->map[i][j] = world->char_map[i][j] - '0';
			else
				world->map[i][j] = -1;
			if (world->map[i][j] == 2)
				world->nb_sprites++;
			j++;
		}
		free(world->char_map[i]);
		i++;
	}
	free(world->char_map);
}

void	cam_init(t_world *world)
{
	if (world->cam_dir == N || world->cam_dir == S)
	{
		world->dir[0] = (world->cam_dir == N) ? -1 : 1;
		world->dir[1] = 0;
		world->cam_plane[0] = 0;
		world->cam_plane[1] = (world->cam_dir == N) ? 0.66 : -0.66;
	}
	else
	{
		world->dir[0] = 0;
		world->dir[1] = (world->cam_dir == W) ? -1 : 1;
		world->cam_plane[0] = (world->cam_dir == W) ? -0.66 : 0.66;
		world->cam_plane[1] = 0;
	}
}

t_bool	sprites_init(t_world *world)
{
	int		i;
	int		j;
	int		index;

	if (!(world->sprites = malloc(world->nb_sprites * sizeof(t_sprite))))
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

void	read_file(t_world *world)
{
	char	*line;
	int		res;
	int		line_nb;

	line_nb = 1;
	while ((res = get_next_line(world->fd, &line)) >= 0)
	{
		parse_line(world, line, line_nb);
		free(line);
		line_nb++;
		if (res == 0)
			break ;
	}
	if (res == -1)
		parsing_error(world, "File is corrupted", 0);
}

t_world	*world_init(int argc, char **argv)
{
	t_world	*world;

	if (!(world = (t_world *)malloc(sizeof(t_world))))
		return (NULL);
	if (!(world->mlx.ptr = mlx_init()))
		return (NULL);
	world->fd = open(argv[1], O_RDONLY);
	read_file(world);
	close(world->fd);
	if (!parse_map(world))
		return (NULL);
	map_init(world);
	cam_init(world);
	if (!sprites_init(world))
		return (NULL);
	world->save = (argc > 2) && (ft_strcmp(argv[2], "-save") == 0);
	if (!init_other_stuff(world))
		return (NULL);
	return (world);
}