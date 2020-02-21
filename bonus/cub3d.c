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

void	game_over(t_world *world)
{
	write_text(world, world->scr_width / 2, world->scr_height / 2 - 20,
		"GAME OVER");
	write_text(world, world->scr_width / 2, world->scr_height / 2,
		"Press ECHAP to quit the game");
	world->game_over = TRUE;
}

int		game_loop(t_world *world)
{
	t_bool	should_draw;

	if (world->game_over)
		return (TRUE);
	should_draw = move(world);
	should_draw = rotate(world) || should_draw;
	should_draw = jump(world) || should_draw;
	if (should_draw)
		draw(world);
	if (world->life <= 0)
		game_over(world);
	return (TRUE);
}

int		main(int argc, char **argv)
{
	t_world		*world;
	pid_t		pid;

	if (!(world = world_init(argc, argv)))
		return (ERROR);
	pid = fork();
	if (pid == 0 && !world->save)
		system("afplay music.mp3");
	else
	{
		draw(world);
		if (!world->save)
		{
			mlx_hook(world->mlx.win, 2, 0, key_pressed, world);
			mlx_hook(world->mlx.win, 3, 0, key_released, world);
			mlx_hook(world->mlx.win, 17, 0, quit, world);
			mlx_loop_hook(world->mlx.ptr, game_loop, world);
			mlx_loop(world->mlx.ptr);
		}
	}
	return (SUCCESS);
}
