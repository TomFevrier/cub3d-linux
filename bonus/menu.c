/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 15:18:10 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_menu(t_world *world, char *folder)
{
	DIR				*dp;
	struct dirent	*ep;
	int				i;

	dp = opendir(folder);
	world->nb_levels = 0;
	while ((ep = readdir(dp)))
		if (!ft_strcmp(ep->d_name + ft_strlen(ep->d_name) - 10, "_bonus.cub"))
			world->nb_levels++;
	closedir(dp);
	world->levels = malloc(world->nb_levels * sizeof(char *));
	dp = opendir(folder);
	i = 0;
	while ((ep = readdir(dp)))
		if (!ft_strcmp(ep->d_name + ft_strlen(ep->d_name) - 10, "_bonus.cub"))
			world->levels[i++] = ft_strdup(ep->d_name);
	closedir(dp);
	world->selected_level = 0;
}

void	fill_screen(t_world *world, int color)
{
	int		i;
	int		j;

	j = 0;
	while (j < world->scr_height)
	{
		i = 0;
		while (i < world->scr_width)
			set_screen_pixel(world->screen, i++, j, color);
		j++;
	}
}

void	draw_menu(t_world *world)
{
	int		i;
	int		pos[2];
	char	*level_name;

	mlx_put_image_to_window(world->mlx.ptr, world->mlx.win,
		world->screen.ptr, 0, 0);
	pos[0] = 640;
	pos[1] = 360 - 50 - world->nb_levels * 15;
	write_text(world, pos, "Cub3D", 0xFFFFFF);
	pos[1] += 50;
	i = 0;
	while (i < world->nb_levels)
	{
		pos[1] += 30;
		level_name = ft_strdup(world->levels[i]);
		write_text(world, pos, format_name(level_name),
		(world->selected_level == i) ? 0xFF0000 : 0xFFFFFF);
		free(level_name);
		i++;
	}
}
