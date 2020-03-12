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

void	parse_texture(t_world *world, char *ptr, t_img *texture, int line_nb)
{
	if (texture->filename)
		parsing_error(world, "Texture was already defined", line_nb);
	while (*ptr <= ' ')
		ptr++;
	texture->filename = ft_strdup(ft_trim(ptr));
	if (open(texture->filename, O_RDONLY) < 0)
		parsing_error(world, "Texture filename is invalid", 0);
}

void	parse_other_line(t_world *world, char *line, int line_nb, int res)
{
	char	*ptr;
	char	*no_spaces;

	ptr = line;
	while (*ptr && *ptr <= ' ')
		ptr++;
	no_spaces = ft_remove_spaces(line);
	if (*ptr == 'M')
	{
		world->music_file = ft_remove_spaces(ptr + 1);
		if (access(world->music_file, F_OK) < 0)
			parsing_error(world, "Music file does not exist", line_nb);
	}
	else if (*ptr == 'P')
		parse_texture(world, ptr + 1, &(world->texture_portal), line_nb);
	else if (ft_strlen(no_spaces) > 0
		&& ft_indexof("0123NWSE", *no_spaces) >= 0)
		read_map_row(world, line);
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
		parse_texture(world, ptr + 2, &(world->textures[N]), line_nb);
	else if (*ptr == 'S' && *(ptr + 1) == 'O')
		parse_texture(world, ptr + 2, &(world->textures[S]), line_nb);
	else if (*ptr == 'W' && *(ptr + 1) == 'E')
		parse_texture(world, ptr + 2, &(world->textures[W]), line_nb);
	else if (*ptr == 'E' && *(ptr + 1) == 'A')
		parse_texture(world, ptr + 2, &(world->textures[E]), line_nb);
	else if (*ptr == 'F')
		parse_texture(world, ptr + 1, &(world->texture_floor), line_nb);
	else if (*ptr == 'S' && *(ptr + 1) == 'K')
		parse_texture(world, ptr + 2, &(world->texture_sky), line_nb);
	else if (*ptr == 'S')
		parse_texture(world, ptr + 1, &(world->texture_sprite), line_nb);
	else
		parse_other_line(world, line, line_nb, res);
}
