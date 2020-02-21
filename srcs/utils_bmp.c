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
