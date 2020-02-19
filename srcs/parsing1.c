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

void	parse_color(t_world *world, char *ptr, char c, int line_nb)
{
	int		r;
	int		g;
	int		b;

	while (*ptr <= ' ')
		ptr++;
	if (*ptr > '9' || *ptr < '0')
		parsing_error(world, "Color is invalid", line_nb);
	r = ft_atoi_easy(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	(*ptr == ',') ? ptr++ : parsing_error(world, "Color is invalid", line_nb);
	if (*ptr > '9' || *ptr < '0')
		parsing_error(world, "Color is invalid", line_nb);
	g = ft_atoi_easy(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	(*ptr == ',') ? ptr++ : parsing_error(world, "Color is invalid", line_nb);
	if (*ptr > '9' || *ptr < '0')
		parsing_error(world, "Color is invalid", line_nb);
	b = ft_atoi_easy(ptr);
	if (c == 'F')
		world->color_floor = (r << 16) + (g << 8) + b;
	else
		world->color_ceiling = (r << 16) + (g << 8) + b;
}

void	parse_texture(t_world *world, char *ptr, int id, int line_nb)
{
	t_img	*texture;

	texture = (id < 4) ? &(world->textures[id]) : &(world->texture_sprite);
	ptr++;
	while (*ptr <= ' ')
		ptr++;
	if (!load_texture(world, texture, ft_trim(ptr)))
		parsing_error(world, "Texture is invalid", line_nb);
}

void	parse_empty_line(t_world *world, char *ptr, int line_nb)
{
	ptr = ft_remove_spaces(ptr);
	if (ft_strlen(ptr) > 0)
		parsing_error(world, "Invalid content", line_nb);
	free(ptr);
}

void	parse_line(t_world *world, char *line, int line_nb)
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
	else if (ft_indexof("012NWSE", *ptr) >= 0)
		read_map_row(world, ptr);
	else
		parse_empty_line(world, ptr, line_nb);
}
