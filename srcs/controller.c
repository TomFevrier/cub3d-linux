/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:24:55 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 15:15:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int key, t_world *world)
{
	if (key == KEY_ESC)
		quit(world, SUCCESS);
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
	return (TRUE);
}

int		key_released(int key, t_world *world)
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
	return (TRUE);
}

int		quit(t_world *world, t_bool exit_value)
{
	free_world(world);
	exit(exit_value);
}
