/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 15:18:10 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	launch_level(char *filename, t_menu *menu)
{
	t_world		*world;
	char		*command;
	char		*tmp;

	write(1, "launch level\n", 13);
	if (!(world = world_init(filename, menu)))
		return (FALSE);
	tmp = ft_strjoin("afplay ", world->music_file);
	command = ft_strjoin(tmp, " &");
	system(command);
	free(tmp);
	free(command);
	draw(world);
	mlx_hook(world->mlx.win, 2, 0, key_pressed, world);
	mlx_hook(world->mlx.win, 3, 0, key_released, world);
	mlx_loop_hook(world->mlx.ptr, game_loop, world);
	mlx_loop(world->mlx.ptr);
	return (TRUE);
}

t_bool	launch_menu(t_menu *menu)
{
	system("afplay ./music/guile.mp3 &");
	write(1, "launch menu\n", 12);
	if (!menu && !(menu = menu_init(1280, 720, "./levels")))
		return (FALSE);
	if (!(menu->mlx.win = mlx_new_window(menu->mlx.ptr,
		menu->scr_width, menu->scr_height, "Cub3D")))
		return (FALSE);
	draw_menu(menu);
	mlx_hook(menu->mlx.win, 2, 0, key_pressed_menu, menu);
	mlx_hook(menu->mlx.win, 17, 0, quit, menu);
	mlx_loop(menu->mlx.ptr);
	return (TRUE);
}

int		main(void)
{
	if (!launch_menu(NULL))
		return (ERROR);
	return (SUCCESS);
}
