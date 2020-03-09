/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
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
	int		pos[2];

	pos[0] = world->scr_width / 2;
	pos[1] = world->scr_height / 2 - 20;
	write_text(world->mlx, pos, "GAME OVER", 0x9F0000);
	pos[1] += 20;
	write_text(world->mlx, pos, "Press ECHAP to return to the main menu",
		0xFFFFFF);
	world->game_over = TRUE;
}

void	you_won(t_world *world)
{
	int		pos[2];

	pos[0] = world->scr_width / 2;
	pos[1] = world->scr_height / 2 - 20;
	write_text(world->mlx, pos, "YOU WON", 0x009F00);
	pos[1] += 20;
	write_text(world->mlx, pos, "Press ECHAP to return to the main menu",
		0xFFFFFF);
}

t_bool	game_loop(t_world *world)
{
	t_bool	should_draw;

	if (world->game_over || world->won)
		return (TRUE);
	should_draw = move(world);
	should_draw = rotate(world) || should_draw;
	should_draw = jump(world) || should_draw;
	should_draw = shoot(world) || should_draw;
	if (should_draw)
		draw(world);
	if (world->life <= 0)
		game_over(world);
	if (world->won)
		you_won(world);
	return (TRUE);
}
