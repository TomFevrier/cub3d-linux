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
	int		pos[2];

	pos[0] = world->scr_width / 2;
	pos[1] = world->scr_height / 2 - 20;
	write_text(world, pos, "GAME OVER", 0x9FFFFF);
	pos[1] += 20;
	write_text(world, pos, "Press ECHAP to return to the main menu", 0xFFFFFF);
	world->game_over = TRUE;
}

t_bool	game_loop(t_world *world)
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

t_bool	launch_level(char *filename)
{
	t_world		*world;
	char		*command;
	char		*tmp;

	write(1, "launch level\n", 13);
	if (!(world = world_init(filename)))
		return (FALSE);
	tmp = ft_strjoin("afplay ", world->music_file);
	command = ft_strjoin(tmp, " &");
	system(command);
	free(tmp);
	free(command);
	draw(world);
	mlx_hook(world->mlx.win, 2, 0, key_pressed, world);
	mlx_hook(world->mlx.win, 3, 0, key_released, world);
	mlx_hook(world->mlx.win, 17, 0, quit, world);
	mlx_loop_hook(world->mlx.ptr, game_loop, world);
	return (TRUE);
}

t_bool	launch_menu(void)
{
	t_world			*world;

	write(1, "launch menu\n", 12);
	if (!(world = (t_world *)calloc(1, sizeof(t_world))))
		return (FALSE);
	if (!(world->mlx.ptr = mlx_init()))
		return (FALSE);
	world->scr_width = 1280;
	world->scr_height = 720;
	if (!(world->mlx.win = mlx_new_window(world->mlx.ptr, world->scr_width,
		world->scr_height, "Cub3D")))
		return (FALSE);
	screen_init(world);
	init_menu(world, "./levels");
	fill_screen(world, 0x000000);
	draw_menu(world);
	mlx_hook(world->mlx.win, 2, 0, key_pressed_menu, world);
	mlx_hook(world->mlx.win, 17, 0, quit, world);
	mlx_loop(world->mlx.ptr);
	return (TRUE);
}

int		main(void)
{
	if (!launch_menu())
		return (ERROR);
	return (SUCCESS);
}
