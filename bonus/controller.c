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

t_bool	key_pressed(int key, t_world *world)
{
	if (key == KEY_ESC)
	{
		free_all(world);
		write(1, "free done\n", 10);
		launch_menu();
	}
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
	else if (key == KEY_F10)
		save_screenshot(world);
	return (TRUE);
}

t_bool	key_pressed_menu(int key, t_world *world)
{
	char	*filename;

	if (key == KEY_ESC)
	{
		free_all(world);
		exit(SUCCESS);
	}
	else if (key == KEY_UP)
		world->selected_level = (world->nb_levels
		+ (world->selected_level - 1)) % world->nb_levels;
	else if (key == KEY_DOWN)
		world->selected_level = (world->selected_level + 1) % world->nb_levels;
	if (key == KEY_UP || key == KEY_DOWN)
		draw_menu(world);
	if (key == KEY_ENTER)
	{
		filename = ft_strjoin("./levels/",
			world->levels[world->selected_level]);
		free_all(world);
		if (!launch_level(filename))
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
	return (TRUE);
}

t_bool	quit(t_world *world)
{
	free_all(world);
	exit(SUCCESS);
}
