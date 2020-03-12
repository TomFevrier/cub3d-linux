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

void	read_file(t_world *world)
{
	char	*line;
	int		res;
	int		line_nb;

	line_nb = 1;
	while ((res = get_next_line(world->fd, &line)) >= 0)
	{
		parse_line(world, line, line_nb, res);
		free(line);
		line_nb++;
		if (res == 0)
			break ;
	}
	if (res == -1)
		parsing_error(world, "File is corrupted", 0);
	close(world->fd);
	if (!world->raw_map)
	{
		parsing_error(world, "Map is not defined", 0);
		quit(world, ERROR);
	}
}

t_world	*world_init(int argc, char **argv)
{
	t_world	*world;

	if (!(world = (t_world *)ft_calloc(1, sizeof(t_world))))
		return (NULL);
	if (argc < 2)
		parsing_error(world, "No scene file specified", 0);
	else if (ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)
		parsing_error(world, "File is invalid: should have extension .cub", 0);
	else if ((world->fd = open(argv[1], O_RDONLY)) < 0)
		parsing_error(world, "File does not exist", 0);
	else
		read_file(world);
	if (world->error)
	{
		if (world->raw_map)
			free(world->raw_map);
		quit(world, ERROR);
	}
	world->save = (argc > 2) && (ft_strcmp(argv[2], "--save") == 0);
	if (!init_other_stuff(world))
		return (NULL);
	return (world);
}
