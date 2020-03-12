/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 15:18:10 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_world		*world;
	char		*command;
	char		*tmp;

	if (!(world = world_init(argc, argv)))
		return (FALSE);
	tmp = ft_strjoin("afplay ", world->music_file);
	command = ft_strjoin(tmp, " &");
	system(command);
	free(tmp);
	free(command);
	draw(world);
	if (!world->save)
	{
		mlx_hook(world->mlx.win, 2, 0, key_pressed, world);
		mlx_hook(world->mlx.win, 3, 0, key_released, world);
		mlx_hook(world->mlx.win, 17, 0, quit, world);
		mlx_loop_hook(world->mlx.ptr, game_loop, world);
		mlx_loop(world->mlx.ptr);
	}
	quit(world, SUCCESS);
	return (SUCCESS);
}
