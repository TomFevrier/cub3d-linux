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

void	free_textures(t_world *world)
{
	t_side	side;

	side = N;
	while (side < E)
	{
		if (world->textures[side].data)
			mlx_destroy_image(world->mlx.ptr, world->textures[side].ptr);
		side++;
	}
}

void	free_world(t_world *world)
{
	int		i;

	if (world->map)
	{
		i = 0;
		while (i < world->map_height)
			free(world->map[i++]);
		free(world->map);
	}
	if (world->sprites)
		free(world->sprites);
	if (world->depth_buffer)
		free(world->depth_buffer);
	if (world->screen.data)
		mlx_destroy_image(world->mlx.ptr, world->screen.ptr);
	if (world->texture_sprite.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_sprite.ptr);
	free_textures(world);
	if (world->mlx.win)
		mlx_destroy_window(world->mlx.ptr, world->mlx.win);
	free(world);
}

int		key_pressed(int key, t_world *world)
{
	if (key == KEY_ESC)
	{
		free_world(world);
		exit(SUCCESS);
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

int		quit(t_world *world)
{
	free_world(world);
	exit(SUCCESS);
}
