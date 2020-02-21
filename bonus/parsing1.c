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
	if (world->scr_width == 0 || world->scr_height == 0 ||
		ft_strlen(ptr) > 0)
		parsing_error(world, "Resolution is invalid", line_nb);
	world->scr_width = world->scr_width > 2560 ? 2560 : world->scr_width;
	world->scr_height = world->scr_height > 1440 ? 1440 : world->scr_height;
	free(ptr);
}

void	parse_texture(t_world *world, char *ptr, int id, int line_nb)
{
	t_img	*texture;

	if (id == 4 && world->texture_sprite.data)
		parsing_error(world, "Sprite texture was already defined", line_nb);
	else if (id == 5 && world->texture_floor.data)
		parsing_error(world, "Floor texture was already defined", line_nb);
	else if (id == 6 && world->texture_sky.data)
		parsing_error(world, "Sky texture was already defined", line_nb);
	else if (id < 4 && world->textures[id].data)
		parsing_error(world, "Wall texture was already defined", line_nb);
	if (id < 4)
		texture = &(world->textures[id]);
	else if (id == 4)
		texture = &(world->texture_sprite);
	else if (id == 5)
		texture = &(world->texture_floor);
	else if (id == 6)
		texture = &(world->texture_sky);
	while (*ptr <= ' ')
		ptr++;
	if (!load_texture(world, texture, ft_trim(ptr)))
		parsing_error(world, "Texture is invalid", line_nb);
}

void	parse_empty_line(t_world *world, char *ptr, int line_nb, int res)
{
	ptr = ft_remove_spaces(ptr);
	if (ft_strlen(ptr) > 0)
		parsing_error(world, "Invalid content", line_nb);
	else if (world->raw_map && res > 0)
		parsing_error(world, "Map contains an empty line", line_nb);
	free(ptr);
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
	else if (*ptr == 'S' && *(ptr + 1) != 'K')
		parse_texture(world, ptr + 1, 4, line_nb);
	else if (*ptr == 'F')
		parse_texture(world, ptr + 1, 5, line_nb);
	else if (*ptr == 'S' && *(ptr + 1) == 'K')
		parse_texture(world, ptr + 2, 6, line_nb);
	else if (ft_indexof("012NWSE", *ptr) >= 0)
		read_map_row(world, ptr);
	else
		parse_empty_line(world, ptr, line_nb, res);
}
