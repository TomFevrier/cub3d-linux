/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:24:55 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/04 15:24:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	back_to_menu(t_world *world)
{
	t_menu	*menu;

	menu = world->menu;
	free_world(world);
	write(1, "free done\n", 10);
	launch_menu(menu);
}

t_bool	key_pressed(int key, t_world *world)
{
	if (key == KEY_ESC)
		back_to_menu(world);
	else if (key == KEY_A)
		world->ctrls.a = TRUE;
	else if (key == KEY_D)
		world->ctrls.d = TRUE;
	else if (key == KEY_W)
		world->ctrls.w = TRUE;
	else if (key == KEY_S)
		world->ctrls.s = TRUE;
	else if (key == KEY_LEFT)
		world->ctrls.left = TRUE;
	else if (key == KEY_RIGHT)
		world->ctrls.right = TRUE;
	else if (key == KEY_UP)
		world->ctrls.up = TRUE;
	else if (key == KEY_DOWN)
		world->ctrls.down = TRUE;
	else if (key == KEY_SPACE)
		world->ctrls.space = TRUE;
	else if (key == KEY_F10)
		save_screenshot(world);
	return (TRUE);
}

t_bool	key_pressed_menu(int key, t_menu *menu)
{
	char	*filename;

	if (key == KEY_ESC)
	{
		free_menu(menu);
		system("killall afplay");
		exit(SUCCESS);
	}
	else if (key == KEY_UP)
		menu->selected_level = (menu->nb_levels
		+ (menu->selected_level - 1)) % menu->nb_levels;
	else if (key == KEY_DOWN)
		menu->selected_level = (menu->selected_level + 1) % menu->nb_levels;
	if (key == KEY_UP || key == KEY_DOWN)
		draw_menu(menu);
	if (key == KEY_ENTER)
	{
		filename = ft_strjoin("./levels/", menu->levels[menu->selected_level]);
		system("killall afplay");
		mlx_destroy_window(menu->mlx.ptr, menu->mlx.win);
		if (!launch_level(filename, menu))
			exit(ERROR);
	}
	return (TRUE);
}

t_bool	key_released(int key, t_world *world)
{
	if (key == KEY_A)
		world->ctrls.a = FALSE;
	else if (key == KEY_D)
		world->ctrls.d = FALSE;
	else if (key == KEY_W)
		world->ctrls.w = FALSE;
	else if (key == KEY_S)
		world->ctrls.s = FALSE;
	else if (key == KEY_LEFT)
		world->ctrls.left = FALSE;
	else if (key == KEY_RIGHT)
		world->ctrls.right = FALSE;
	else if (key == KEY_UP)
		world->ctrls.up = FALSE;
	else if (key == KEY_DOWN)
		world->ctrls.down = FALSE;
	else if (key == KEY_SPACE)
	{
		world->ctrls.space = FALSE;
		if (!world->game_over && !world->won)
			draw(world);
	}
	return (TRUE);
}

t_bool	quit(t_menu *menu)
{
	free_menu(menu);
	system("killall afplay");
	exit(SUCCESS);
}
