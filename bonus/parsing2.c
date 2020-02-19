/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
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
	close(world->fd);
	free_all(world);
	exit(ERROR);
}

void	parse_map_row(t_world *world, int i)
{
	int		j;

	j = 0;
	while (world->raw_map[j] && world->raw_map[j] != '\n')
		j++;
	world->char_map[i] = ft_substr(world->raw_map, 0, j);
	world->raw_map += j + 1;
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
	if (!(world->char_map = malloc(world->map_height * sizeof(char *))))
		return (FALSE);
	ptr = world->raw_map;
	i = 0;
	world->map_width = 0;
	while (i < world->map_height)
		parse_map_row(world, i++);
	free(ptr);
	if (!check_map(world))
		parsing_error(world, "Map is invalid", 0);
	return (TRUE);
}

void	read_map_row(t_world *world, char *ptr)
{
	char	*tmp;

	check_missing(world);
	ptr = ft_remove_spaces(ptr);
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
	free(ptr);
}
