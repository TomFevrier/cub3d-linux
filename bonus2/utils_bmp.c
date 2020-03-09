/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	number_to_mem(char *dest, int nb, int nb_bytes)
{
	int		shift;
	int		i;

	i = nb_bytes - 1;
	shift = (nb_bytes > 1) ? (nb_bytes - 1) * 8 : 0;
	while (shift > 0)
	{
		dest[i] = (nb >> shift) & 0xFF;
		shift -= 8;
		i--;
	}
	dest[i] = nb & 0xFF;
}

void	write_bmp_header(t_world *world)
{
	char	header[54];

	header[0] = 'B';
	header[1] = 'M';
	number_to_mem(&header[2], 54 + world->nb_pixels, 4);
	number_to_mem(&header[6], 0, 4);
	number_to_mem(&header[10], 54, 4);
	number_to_mem(&header[14], 40, 4);
	number_to_mem(&header[18], world->scr_width, 4);
	number_to_mem(&header[22], world->scr_height, 4);
	number_to_mem(&header[26], 1, 2);
	number_to_mem(&header[28], world->screen.bpp, 2);
	number_to_mem(&header[30], 0, 4);
	number_to_mem(&header[34], world->nb_pixels, 4);
	number_to_mem(&header[38], 0, 16);
	write(world->fd_save, header, 54);
}

void	flip_pixels(t_world *world)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while (i < world->scr_width)
	{
		j = 0;
		while (j < world->scr_height / 2)
		{
			tmp = get_screen_pixel(world->screen, i, j);
			set_screen_pixel(world->screen, i, j,
				get_screen_pixel(world->screen, i, world->scr_height - j - 1));
			set_screen_pixel(world->screen, i, world->scr_height - j - 1, tmp);
			j++;
		}
		i++;
	}
}

void	save_screenshot(t_world *world)
{
	static char	filename[18] = "screenshot_00.bmp";
	int			pos[2];

	filename[11] = '0' + world->screenshot_index / 10;
	filename[12] = '0' + world->screenshot_index % 10;
	world->save = TRUE;
	world->fd_save = open(filename, O_WRONLY | O_CREAT, 0777);
	write_bmp_header(world);
	draw(world);
	close(world->fd_save);
	world->save = FALSE;
	world->screenshot_index = (world->screenshot_index + 1) % 100;
	pos[0] = world->scr_width / 2;
	pos[1] = 10;
	write_text(world->mlx, pos, "Screenshot saved!", 0xFFFFFF);
}
