/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/02/14 18:46:23 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	screen_init(t_world *world)
{
	if (!(world->screen.ptr = mlx_new_image(world->mlx.ptr,
		world->scr_width, world->scr_height)))
		return (FALSE);
	if (!(world->screen.data = mlx_get_data_addr(world->screen.ptr,
		&(world->screen.bpp), &(world->screen.size_line),
		&(world->screen.endian))))
		return (FALSE);
	return (TRUE);
}

t_bool	init_other_stuff(t_world *world)
{
	if (!(world->depth_buffer = malloc(world->scr_width * sizeof(double))))
		return (FALSE);
	if (!screen_init(world))
		return (FALSE);
	world->nb_pixels = world->scr_width * world->scr_height *
		(world->screen.bpp >> 3);
	if (world->save)
	{
		world->fd_save = open("cub3d.bmp", O_WRONLY | O_CREAT, 0777);
		write_bmp_header(world);
	}
	else if (!(world->mlx.win = mlx_new_window(world->mlx.ptr, world->scr_width,
		world->scr_height, "Cub3D")))
		return (FALSE);
	return (TRUE);
}
