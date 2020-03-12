/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(t_world *world, char *ptr, int line_nb)
{
	if (world->scr_width)
		parsing_error(world, "Resolution was already defined", line_nb);
	while (*ptr <= ' ')
		ptr++;
	world->scr_width = ft_atoi_easy(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	while (*ptr <= ' ')
		ptr++;
	world->scr_height = ft_atoi_easy(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	ptr = ft_remove_spaces(ptr);
	if (world->scr_width == 0 || world->scr_height == 0 || ft_strlen(ptr) > 0)
		parsing_error(world, "Resolution is invalid", line_nb);
	world->scr_width = world->scr_width > 2560 ? 2560 : world->scr_width;
	world->scr_height = world->scr_height > 1440 ? 1440 : world->scr_height;
	world->scr_width = world->scr_width < 100 ? 100 : world->scr_width;
	world->scr_height = world->scr_height < 100 ? 100 : world->scr_height;
	free(ptr);
}

void	parse_color(t_world *world, char *ptr, char c, int line_nb)
{
	int		color;
	int		i;

	if (c == 'F' && world->color_floor)
		parsing_error(world, "Floor color was already defined", line_nb);
	if (c == 'C' && world->color_ceiling)
		parsing_error(world, "Ceiling color was already defined", line_nb);
	i = 0;
	color = 0;
	while (i++ < 3)
	{
		while (*ptr <= ' ')
			ptr++;
		if (*ptr > '9' || *ptr < '0')
			parsing_error(world, "Color is invalid", line_nb);
		color = (color << 8) + ft_atoi_easy(ptr);
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
		(*ptr == ',' || i == 3) ? ptr++
			: parsing_error(world, "Color is invalid", line_nb);
	}
	if (c == 'F')
		world->color_floor = color;
	else
		world->color_ceiling = color;
}

void	parse_texture(t_world *world, char *ptr, int id, int line_nb)
{
	t_img	*texture;

	if (id == 4 && world->texture_sprite.filename)
		parsing_error(world, "Sprite texture was already defined", line_nb);
	else if (id < 4 && world->textures[id].filename)
		parsing_error(world, "Wall texture was already defined", line_nb);
	else
	{
		texture = (id < 4) ? &(world->textures[id]) : &(world->texture_sprite);
		while (*ptr <= ' ')
			ptr++;
		texture->filename = ft_strdup(ft_trim(ptr));
		if (open(texture->filename, O_RDONLY) < 0)
			parsing_error(world, "Texture filename is invalid", 0);
	}
}

void	parse_other_line(t_world *world, char *ptr, int line_nb, int res)
{
	char	*no_spaces;

	no_spaces = ft_remove_spaces(ptr);
	if (ft_strlen(no_spaces) > 0 && ft_indexof("012NWSE", *no_spaces) >= 0)
		read_map_row(world, ptr);
	else if (world->raw_map && res > 0)
		parsing_error(world, "Map contains an empty line", line_nb);
	free(no_spaces);
}

void	parse_line(t_world *world, char *line, int line_nb, int res)
{
	char	*ptr;

	ptr = line;
	while (*ptr && *ptr <= ' ')
		ptr++;
	if (*ptr == 'R')
		parse_resolution(world, ptr + 1, line_nb);
	else if (*ptr == 'N' && *(ptr + 1) == 'O')
		parse_texture(world, ptr + 2, N, line_nb);
	else if (*ptr == 'S' && *(ptr + 1) == 'O')
		parse_texture(world, ptr + 2, S, line_nb);
	else if (*ptr == 'W' && *(ptr + 1) == 'E')
		parse_texture(world, ptr + 2, W, line_nb);
	else if (*ptr == 'E' && *(ptr + 1) == 'A')
		parse_texture(world, ptr + 2, E, line_nb);
	else if (*ptr == 'F' || *ptr == 'C')
		parse_color(world, ptr + 1, *ptr, line_nb);
	else if (*ptr == 'S')
		parse_texture(world, ptr + 1, 4, line_nb);
	else
		parse_other_line(world, line, line_nb, res);
}
