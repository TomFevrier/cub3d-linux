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

void	read_levels(t_menu *menu, char *folder)
{
	DIR				*dp;
	struct dirent	*ep;
	int				i;

	menu->nb_levels = 0;
	dp = opendir(folder);
	while ((ep = readdir(dp)))
		if (!ft_strcmp(ep->d_name + ft_strlen(ep->d_name) - 10, "_bonus.cub"))
			menu->nb_levels++;
	closedir(dp);
	menu->levels = malloc(menu->nb_levels * sizeof(char *));
	dp = opendir(folder);
	i = 0;
	while ((ep = readdir(dp)))
		if (!ft_strcmp(ep->d_name + ft_strlen(ep->d_name) - 10, "_bonus.cub"))
			menu->levels[i++] = ft_strdup(ep->d_name);
	closedir(dp);
}

t_menu	*menu_init(int width, int height, char *folder)
{
	t_menu			*menu;

	if (!(menu = calloc(1, sizeof(t_menu))))
		return (NULL);
	if (!(menu->mlx.ptr = mlx_init()))
		return (NULL);
	menu->scr_width = width;
	menu->scr_height = height;
	read_levels(menu, folder);
	menu->selected_level = 0;
	return (menu);
}

void	draw_menu(t_menu *menu)
{
	int		i;
	int		pos[2];
	char	*level_name;

	mlx_clear_window(menu->mlx.ptr, menu->mlx.win);
	pos[0] = 640;
	pos[1] = 360 - 50 - menu->nb_levels * 15;
	write_text(menu->mlx, pos, "Cub3D", 0xFFFFFF);
	pos[1] += 50;
	i = 0;
	while (i < menu->nb_levels)
	{
		pos[1] += 30;
		level_name = ft_strdup(menu->levels[i]);
		write_text(menu->mlx, pos, format_name(level_name),
		(menu->selected_level == i) ? 0x9F0000 : 0xFFFFFF);
		free(level_name);
		i++;
	}
}
