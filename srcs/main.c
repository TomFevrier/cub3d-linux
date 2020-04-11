/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 14:36:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		game_loop(t_world *world)
{
	t_bool	should_draw;

	should_draw = move(world);
	should_draw = rotate(world) || should_draw;
	if (should_draw)
		draw(world);
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_world		*world;

	if (!(world = world_init(argc, argv)))
		return (ERROR);
	draw(world);
	if (!world->save)
	{
		mlx_hook(world->mlx.win, 2, 1L << 0, key_pressed, world);
		mlx_hook(world->mlx.win, 3, 1L << 1, key_released, world);
		mlx_hook(world->mlx.win, 17, 0, quit, world);
		mlx_loop_hook(world->mlx.ptr, game_loop, world);
		mlx_loop(world->mlx.ptr);
	}
	quit(world, SUCCESS);
	return (SUCCESS);
}
